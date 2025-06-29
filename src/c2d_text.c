#include "core2d.h"

int InitializeFontSubsystem()
{
    return TTF_Init();
}

int NewTextFont(TextFont* font, const char *path, int fontSize)
{
    Log("Loading font '%s'...", path);

    TTF_Font* tmpFont = TTF_OpenFont(path, fontSize);

    if (tmpFont == NULL){
        Err("Failed to load font: %s", path);
        PushError("Failed to load font: %s", path);
        Log("Error message: %s", TTF_GetError());
        return 1;
    }

    font->font = tmpFont;
    return 0;
}

int NewText(Text* out, Window* win, TextFont *font, const char *text, Color color)
{
    return NewTextEx(out, win, font, text, color, false);
}

int NewTextEx(Text* out, Window *win, TextFont *font, const char *text, Color color, bool blend)
{
    if (font == NULL){
        Err("Font provided was null.");
        PushError("Font provided was null.");
        return 1;
    }

    SDL_Surface* textSurface = NULL;
    
    if (!blend) textSurface = TTF_RenderText_Solid(font->font, text, (SDL_Color){ color.r, color.g, color.b, color.a });
    else textSurface = TTF_RenderText_Blended(font->font, text, (SDL_Color){ color.r, color.g, color.b, color.a });

    if (textSurface == NULL){
        Err("Failed to render text '%s'.", text);
        PushError("Failed to render text '%s'.", text);
        Log("Error message: %s", TTF_GetError);
        return 1;
    }

    out->tex = SDL_CreateTextureFromSurface(win->renderer, textSurface);
    out->height = textSurface->h;
    out->width = textSurface->w;

    SDL_FreeSurface(textSurface);

    return 0;
}

void FreeText(Text *text)
{
    Log("Unloading text...");
    SDL_DestroyTexture(text->tex);
}

void FreeTextFont(TextFont *font)
{
    Log("Unloading font...");
    TTF_CloseFont(font->font);
}

