#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Timer* timer = NewTimer(10.0f, true);

    while (WindowIsOpen(win)){
        UpdateTimer(timer);
        Log("Time elapsed: %f/%f", timer->remaining, timer->maxDuration);

        RenderFill(win, defaultColors[WHITE]);
        RenderShow(win);
    }

    FreeTimer(timer);
    DestroyWindow(win);
    Quit();
    return 0;
}