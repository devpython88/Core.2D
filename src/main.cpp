#include "core2d.h"
#include <string>

int main() {
    Window win;
    NewWindow(&win, "Test", 640, 480, 60);

    Rectangle rec = { 20, 20, 50, 50 };    

    bool run = true;
    while (run){
        UpdateDeltaTime();
        FetchEvents(&win);
        if (IsEvent(&win, SDL_QUIT)){
            run = false;
        }

        if (IsKeyHeld(SDLK_w)){
            Log("Hello there!");
        }

        // This is when the key is held

        RenderFill(&win, WHITE);
        RenderFillRect(&win, rec, RED);
        RenderShow(&win);
    }

    DestroyWindow(&win);
    Quit();
    return 0;
}