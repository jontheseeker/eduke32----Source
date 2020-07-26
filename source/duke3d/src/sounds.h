//-------------------------------------------------------------------------
/*
Copyright (C) 2010 EDuke32 developers and contributors

This file is part of EDuke32.

EDuke32 is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License version 2
as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
//-------------------------------------------------------------------------

//****************************************************************************
//
// sounds.h
//
//****************************************************************************

#ifndef sounds_public_h_
#define sounds_public_h_

#include "sounds_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAXSOUNDS           16384
#define MAXSOUNDINSTANCES   8
#define LOUDESTVOLUME       111
#define MUSIC_ID            (-65536)
#define MAXVOICES           128

typedef struct
{
    int16_t  owner;
    int16_t  id;
    uint16_t dist;
    uint16_t clock;
} assvoice_t;

typedef struct
{
    int16_t    playing;
    assvoice_t voices[MAXSOUNDINSTANCES];
    char *     ptr;
    int32_t    siz;
    float      volume;
    int16_t    pitchMin, pitchMax, distOffset;
    char       priority, mode;
    char       lock;
    char *     filename;
} sound_t;

extern sound_t nullsound;
extern sound_t **g_sounds;
extern int32_t g_numEnvSoundsPlaying,g_highestSoundIdx;

int A_CheckSoundPlaying(int spriteNum,int soundNum);
int A_PlaySound(int soundNum, int spriteNum);
void S_Callback(intptr_t num);
int A_CheckAnySoundPlaying(int spriteNum);
int S_CheckSoundPlaying(int soundNum);
void S_Cleanup(void);
void S_ClearSoundLocks(void);
int32_t S_LoadSound(uint32_t num);
void cacheAllSounds(void);
void S_MenuSound(void);
void S_MusicShutdown(void);
void S_MusicStartup(void);
void S_MusicVolume(int32_t volume);
void S_RestartMusic(void);
void S_PauseMusic(bool paused);
void S_PauseSounds(bool paused);
bool S_TryPlayLevelMusic(unsigned int m);
void S_PlayLevelMusicOrNothing(unsigned int);
int S_TryPlaySpecialMusic(unsigned int);
void S_PlaySpecialMusicOrNothing(unsigned int);
void S_ContinueLevelMusic(void);
int S_PlaySound(int num);
int S_PlaySound3D(int num, int spriteNum, const vec3_t *pos);
void S_SoundShutdown(void);
void S_AllocIndexes(int sndidx);
void S_SoundStartup(void);
void S_StopEnvSound(int sndNum,int sprNum);
void S_StopAllSounds(void);
void S_StopMusic(void);
void S_Update(void);
void S_ChangeSoundPitch(int soundNum, int spriteNum, int pitchoffset);
int32_t S_GetMusicPosition(void);
void S_SetMusicPosition(int32_t position);

static FORCE_INLINE bool S_IsAmbientSFX(int const spriteNum) { return (sprite[spriteNum].picnum == MUSICANDSFX && sprite[spriteNum].lotag < 999); }

#ifdef __cplusplus
}
#endif

#endif
