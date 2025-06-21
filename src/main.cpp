#include "core2d.h"

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Texture* ball = NewTexture(win, "ball.png", 70, 120);

    while (WindowIsOpen(win)){
        RenderFill(win, defaultColors[WHITE]);
        RenderDrawTextureEx(win, (Vector2i) { 0, 0 }, ball, (Rectangle) { 0, 0, 8, 8 } );
        RenderShow(win);
    }

    FreeTexture(ball);
    DestroyWindow(win);
    return 0;
}