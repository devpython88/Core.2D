#include "core2d.h"

int InitializeFontSubsystem()
{
    return TTF_Init();
}

TextFont *NewTextFont(const char *path, int fontSize)
{
    Log("Loading font '%s'...", path);

    TextFont* font = (TextFont*)malloc(sizeof(TextFont));

    TTF_Font* tmpFont = TTF_OpenFont(path, fontSize);

    if (tmpFont == NULL){
        Err("Failed to load font: %s", path);
        Log("Error message: %s", TTF_GetError());
        return NULL;
    }

    font->font = tmpFont;
    return font;
}

Text *NewText(Window* win, TextFont *font, const char *text, Color color)
{
    NewTextEx(win, font, text, color, false);
}

Text *NewTextEx(Window *win, TextFont *font, const char *text, Color color, bool blend)
{
    if (font == NULL){
        Err("Font provided was null.");
        return NULL;
    }

    Text* pText = (Text*)malloc(sizeof(Text));

    SDL_Surface* textSurface = NULL;
    
    if (!blend) textSurface = TTF_RenderText_Solid(font->font, text, (SDL_Color){ color.r, color.g, color.b, color.a });
    else textSurface = TTF_RenderText_Blended(font->font, text, (SDL_Color){ color.r, color.g, color.b, color.a });

    if (textSurface == NULL){
        Err("Failed to render text '%s'.", text);
        Log("Error message: %s", TTF_GetError);
        return NULL;
    }

    pText->tex = SDL_CreateTextureFromSurface(win->renderer, textSurface);
    pText->height = textSurface->h;
    pText->width = textSurface->w;

    SDL_FreeSurface(textSurface);

    return pText;
}

void FreeText(Text *text)
{
    Log("Unloading text...");
    SDL_DestroyTexture(text->tex);
    free(text);
}

void FreeTextFont(TextFont *font)
{
    Log("Unloading font...");
    TTF_CloseFont(font->font);
    free(font);
}

