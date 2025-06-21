# Core.2D
Core is a replacement for my old game library (nova.h), It is made in C which means its not OOP but I am dedicating myself to make this library a good library and not buggy like my previous game library


Core is built ontop of SDL2 and adds many features that SDL2 doesn't have (for ex. Camera) Here is a example of loading a texture:

```cpp
#include "core2d.h"

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Texture* ball = NewTexture(win, "ball.png", 50, 50); // file path, scaled width, scaled height

    while (WindowIsOpen(win)){
        RenderFill(win, defaultColors[WHITE]);
        RenderDrawTexture(win, 100, 0, ball); // Draw the whole texture
        RenderDrawTextureEx(win, (Vector2i) { 0, 0 }, ball, (Rectangle) { 0, 0, 8, 8 } ); // Draw a cutout from the texture
        RenderShow(win);
    }

    FreeTexture(ball); // free the texture
    DestroyWindow(win);
    Quit();
    return 0;
}
```