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
        RenderDrawSpritesheet(win, 20, 20, sheet);
        RenderShow(win);
    }

    FreeSpritesheet(sheet);
    FreeTexture(ballTex);
    DestroyWindow(win);
    Quit();
    return 0;
}