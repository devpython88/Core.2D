#include "core2d.h"

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Rectangle rec = { 20, 20, 50, 50 };
    Circle circle = { 100, 100, 50 };

    while (WindowIsOpen(win)){
        RenderFill(win, Color{255, 255, 255, 255});
        RenderLinesRect(win, rec, Color{255, 0, 0, 255});
        RenderFillCircle(win, circle, Color{0, 255, 0, 255});
        RenderDrawPoint(win, 200, 200, Color{255, 0, 0, 0});
        RenderDrawLine(win, Vector2i{300, 300}, Vector2i{500, 500}, Color{255, 0, 0, 0});
        RenderShow(win);
    }

    DestroyWindow(win);
    return 0;
}