#include "core2d.h"


int InitializeSFXSubsystem(int frequency, Uint16 format, int channels, int chunksize)
{
    return Mix_OpenAudio(frequency, format, channels, chunksize);
}

int InitializeSFXFor(int format)
{
    return Mix_Init(format);
}

Music *NewMusicStream(const char *path)
{
    Log("Loading music '%s'...", path);
    Mix_Music* sdlMus = Mix_LoadMUS(path);
    if (sdlMus == NULL){
        Err("Failed to load music '%s'.", path);
        Log("Error message: %s", Mix_GetError());
        return NULL;
    }
    
    Music* music = (Music*)malloc(sizeof(Music));
    
    music->content = sdlMus;

    return music;
}

Sound *NewSound(const char *path)
{
    Log("Loading sound '%s'...", path);
    Mix_Chunk* sdlChunk = Mix_LoadWAV(path);
    if (sdlChunk == NULL){
        Err("Failed to load chunk '%s'.", path);
        Log("Error message: %s", Mix_GetError());
        return NULL;
    }
    
    Sound* sound = (Sound*)malloc(sizeof(Sound));
    sound->chunk = sdlChunk;

    return sound;
}

void FreeMusicStream(Music *music)
{
    Mix_FreeMusic(music->content);
    free(music);
}

void FreeSound(Sound *sound)
{
    Mix_FreeChunk(sound->chunk);
    free(sound);
}

void PlayMusicStream(Music *music, int loops)
{
    Mix_PlayMusic(music->content, loops);
}

bool PlayingMusic()
{   
    return Mix_PlayingMusic();
}

void PauseMusic()
{
    Mix_PauseMusic();
}

void ResumeMusic()
{
    Mix_ResumeMusic();
}

void PlaySound(Sound *sound, int channel, int loops)
{
    Mix_PlayChannel(channel, sound->chunk, loops);
}
