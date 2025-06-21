#include "core2d.h"

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Rectangle rec = { 20, 20, 50, 50 };
    Circle circle = { 100, 100, 50 };

    int* nums = ARR_ALLOC(int, 5);
    
    for (int i = 0; i < 5; i++){
        nums[i] = 10;
        Log("%d", nums[i]);
    }

    int* nums2 = ARR_RESIZE(nums, int, 6);
    nums = nums2;
    nums[5] = 20;
    Log("%d", nums[5]);
    ARR_DESTROY(nums2);

    while (WindowIsOpen(win)){
        if (win->event.type == SDL_KEYDOWN){
            if (GetKeycode(win) == SDLK_w){
                currentCamera->targetX += 10;
            }

            if (GetKeycode(win) == SDLK_s){
                currentCamera->targetX -= 10;
            }
        }


        RenderFill(win, defaultColors[WHITE]);
        DisableCamera();
        RenderLinesRect(win, rec, defaultColors[RED]);
        RenderFillCircle(win, circle, defaultColors[BLUE]);
        RenderDrawPoint(win, 200, 200, defaultColors[GREEN]);
        RenderDrawLine(win, Vector2i{300, 300}, Vector2i{500, 500}, defaultColors[MAGENTA]);
        RenderShow(win);
    }

    DestroyWindow(win);
    return 0;
}