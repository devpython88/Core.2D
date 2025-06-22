#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);
    InitializeSFXSubsystem(21400, MIX_DEFAULT_FORMAT, 2, 2048);
    InitializeSFXFor(MIX_INIT_MP3);

    Music* music = NewMusicStream("./bang.mp3");
    PlayMusicStream(music, INF_LOOP);

    while (WindowIsOpen(win)){
        RenderFill(win, defaultColors[WHITE]);
        RenderShow(win);
    }

    FreeMusicStream(music);
    DestroyWindow(win);
    Quit();
    return 0;
}