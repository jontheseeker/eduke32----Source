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

#ifndef mempool_h__
#define mempool_h__

#include "allocator.h"
#include "stacklist.h"

class PoolAllocator : public Allocator
{
  private:
    struct FreeHeader
    {
    };
    using Node = StackLinkedList<FreeHeader>::Node;
    StackLinkedList<FreeHeader> m_freeList = {};

    void * m_start_ptr = nullptr;
    size_t m_chunkSize;

  public:
    PoolAllocator(size_t const totalSize, size_t const chunkSize);

    virtual ~PoolAllocator();

    virtual void *Allocate(size_t const size, size_t const alignment = 0) override;

    virtual void Free(void *ptr) override;

    virtual void Init() override;

    virtual void Reset();

  private:
    PoolAllocator(PoolAllocator &poolAllocator);
};
#endif  // mempool_h__
