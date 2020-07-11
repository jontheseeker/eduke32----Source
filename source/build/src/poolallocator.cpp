/* 
MIT License

Copyright (c) 2016 Mariano Trebino
Copyright (c) 2020 EDuke32 developers and contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "poolallocator.h"

#include "compat.h"

PoolAllocator::PoolAllocator(size_t const totalSize, size_t const chunkSize) : Allocator(totalSize)
{
    Bassert(chunkSize >= 8 && totalSize % chunkSize == 0);
    m_chunkSize = chunkSize;
}

void PoolAllocator::Init()
{
    m_start_ptr = Bmalloc(m_totalSize);
    this->Reset();
}

PoolAllocator::~PoolAllocator() { Bfree(m_start_ptr); }

void *PoolAllocator::Allocate(size_t const allocationSize, size_t const)
{
    Bassert(allocationSize == m_chunkSize);

#ifdef NDEBUG
    if (allocationSize != m_chunkSize)
        return nullptr;
#endif
    Node *freePosition = m_freeList.pop();

    if (freePosition == nullptr)
        return nullptr;

    m_used += m_chunkSize;
    m_peak = max(m_peak, m_used);

    return (void *)freePosition;
}

void PoolAllocator::Free(void *ptr)
{
#ifndef NDEBUG
    auto cp = (uint8_t *)ptr, sp = (uint8_t *)m_start_ptr;
    Bassert(cp >= sp && cp <= sp + m_totalSize - m_chunkSize);
#endif
    m_used -= m_chunkSize;
    m_freeList.push((Node *)ptr);
}

void PoolAllocator::Reset()
{
    m_used = 0;
    m_peak = 0;
    // Create a linked-list with all free positions
    int const nChunks = tabledivide32_noinline(m_totalSize, m_chunkSize);
    for (int i = 0; i < nChunks; ++i)
    {
        size_t address = (size_t)m_start_ptr + i * m_chunkSize;
        m_freeList.push((Node *)address);
    }
}
