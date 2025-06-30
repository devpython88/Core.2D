#include "core2d.h"
#include <string>

int main() {
    InitializeCore2D();
    
    Window win;
    NewWindow(&win, "Test", 640, 480, 60);

    Rectangle rec = { 20, 20, 50, 50 };    
    Rectangle rec2 = { 20, 200, 50, 50 };    

    bool run = true;

    Vector2f start1 = { 0.0f, 0.0f };
    Vector2f end1 = { 100.0f, 50.0f };

    Vector2f start2 = { 60.0f, 100.0f };
    Vector2f end2 = { 60.0f, 0.0f };

    while (run){
        UpdateDeltaTime();

        FetchEvents(&win);
        if (IsEvent(&win, SDL_QUIT)){
            run = false;
        }

        if (IsKeyHeld(SDLK_d)){
            end2.x += 2.5f;
            start2.x += 2.5f;
        }

        if (IsKeyHeld(SDLK_a)){
            end2.x -= 2.5f;
            start2.x -= 2.5f;
        }
        
        // set normal posiiton
        end1 = { 100.0f, 50.0f };
    
        AreLinesColliding(
            start1, end1, start2, end2,
            &end1
        );
        // set end to collision point

        RenderFill(&win, WHITE);

        // draw lines
        RenderDrawLine(&win, start1, end1, RED);
        RenderDrawLine(&win, start2, end2, RED);

        // RenderFillRect(&win, rec, RED);
        // RenderFillRect(&win, rec2, BLUE);

        RenderShow(&win);
    }

    DestroyWindow(&win);
    Quit();
    return 0;
}

