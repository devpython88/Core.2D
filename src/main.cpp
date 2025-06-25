#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    // Make a timer
    Timer* timer = NewTimer(10.0f, false);

    while (WindowIsOpen(win)){
        // Replace timer on finish
        // You can also use ResetTimer to reset
        if (IsFinished(timer)){
            ReplaceTimer(timer, 4.5f, false);
        }

        // Update the timer
        UpdateTimer(timer);
        
        // Print elapsed time
        Log("Time elapsed: %f/%f", GetElapsed(timer), timer->maxDuration);

        RenderFill(win, defaultColors[WHITE]);
        RenderShow(win);
    }

    // Free timer
    FreeTimer(timer);
    DestroyWindow(win);
    Quit();
    return 0;
}