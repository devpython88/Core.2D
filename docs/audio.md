# Audio in Core.2D
in core.2d or core for short, Audio is a little bit verbose but still simple enough to use.

1. Initialize the subsystem
```cpp
InitializeSFXSubsystem(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048); // frequency, format, channels, chunkSize
```

2. Initialize needed sub-subsystems
```cpp
InitializeSFXFor(MIX_INIT_MP3); // Wave is automatically initialized.
```

3. Load a music or sound
```cpp
Music* mus = NewMusicStream("mymus.mp3");

PlayMusicStream(mus, INF_LOOP); // replace inf_loop with number of loops if you dont want an endless music
// dont run this in the game loop otherwise it will restart over and over


// SOUNDS
Sound* sound = NewSound("mysound.wav");
PlaySound(sound, NEAREST_AVAILABLE_CHANNEL, INF_LOOP);
```

4. Freeing
```cpp
FreeMusicStream(mus);
FreeSound(sound);
```


## Cheatsheet


`int InitializeSFXSubsystem(int frequency, Uint16 format, int channels, int chunksize)`: init subsys
`int InitializeSFXFor(int format)`: init subsys for `format`

`Music* NewMusicStream(const char* path)`: make new music
`Sound* NewSound(const char* path)`: make new sound

`void FreeMusicStream(Music* music)`: free music
`void FreeSound(Sound* sound)`: free sound

`void PlayMusicStream(Music* music, int loops)`: play music
`bool PlayingMusic()`: check if some music is playing
`void PauseMusic()`: pause any playing music
`void ResumeMusic()`: resume any paused music

`void PlaySound(Sound* sound, int channel, int loops)`: play sound
