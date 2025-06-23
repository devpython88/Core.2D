#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);
    InitializeImageSubsystemForPNG();
    
    Texture* ballTex = NewTexture(win, "ball.png", 50, 50);

    Spritesheet* sheet = NewSpritesheet(ballTex, 4, 4);

    while (WindowIsOpen(win)){
        if (IsMousePressed(win, SDL_BUTTON_LEFT))
            sheet->col++;
        
        Log("Mouse: %d %d", mousePosition.x, mousePosition.y);
        
        RenderFill(win, defaultColors[WHITE]);
        RenderDrawTexturePro(win,
            Vector2i{20, 20},
            ballTex,
            GetRectangleFromTexture(ballTex),
            Vector2i{0, 0},
            45, SDL_FLIP_NONE);
        RenderShow(win);
    }

    FreeSpritesheet(sheet);
    FreeTexture(ballTex);
    DestroyWindow(win);
    Quit();
    return 0;
}