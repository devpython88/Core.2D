#include "core2d.h"
#include <string>

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);
    InitializeFontSubsystem();

    TextFont* font = NewTextFont("./arial.ttf", 30);

    int score = 0;
    std::string textStr = "Score: " + std::to_string(score);

    std::string oldStr = textStr;
    Text* text = NewTextEx(win, font, textStr.c_str(), defaultColors[RED], true);

    while (WindowIsOpen(win)){
        if (GetPressed(win, SDLK_w)){
            score += 1;
            textStr = "Score: " + std::to_string(score);
        }

        if (oldStr != textStr){
            FreeText(text);
            text = NewTextEx(win, font, textStr.c_str(), defaultColors[RED], true);
            oldStr = textStr;
        }

        RenderFill(win, defaultColors[WHITE]);
        RenderDrawText(win, text, 0, 0);
        RenderShow(win);
    }

    FreeText(text);
    FreeTextFont(font);
    DestroyWindow(win);
    Quit();
    return 0;
}