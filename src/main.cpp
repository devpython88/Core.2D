#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);
    
    const char* text = QuickFileRead("dumb.txt");
    Log("Text: %s", text);
    free((void*)text);

    while (WindowIsOpen(win)){
        if (IsMousePressed(win, SDL_BUTTON_LEFT)){

        }
        
        RenderFill(win, defaultColors[WHITE]);
        RenderShow(win);
    }

    DestroyWindow(win);
    Quit();
    return 0;
}