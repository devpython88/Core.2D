#include "core2d.h"
#include <string>

int main() {
    Window win;
    NewWindow(&win, "Test", 640, 480, 60);

    InitializeImageSubsystemForPNG();
    InitializeFontSubsystem();
    InitializeSFXSubsystem(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048);
    InitializeSFXFor(MIX_INIT_MP3);

    Sound sound;
    NewSound(&sound, "bang.mp3");

    PlaySound(&sound, NEAREST_AVAILABLE_CHANNEL, 5);

    Texture texture;
    Spritesheet sheet;

    NewTexture(&texture, &win, "ball.png", 32, 32);
    NewSpritesheet(&sheet, &texture, 8, 8);

    TextFont font;
    Text text;

    NewTextFont(&font, "arial.ttf", 32);
    NewText(&text, &win, &font, "Hello", defaultColors[BLACK]);

    while (WindowIsOpen(&win)){
        if (IsMousePressed(&win, SDL_BUTTON_LEFT)){
            sheet.col++;
            if (sheet.col > 1){
                sheet.col = 0;
            }
        }

        RenderFill(&win, defaultColors[WHITE]);
        RenderDrawText(&win, &text, 0, 0);
        RenderDrawSpritesheet(&win, 100, 0, &sheet);
        RenderShow(&win);
    }

    FreeTexture(&texture);
    FreeSound(&sound);
    FreeTextFont(&font);
    FreeText(&text);

    DestroyWindow(&win);
    Quit();
    return 0;
}