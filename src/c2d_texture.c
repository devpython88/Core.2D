#include "core2d.h"

int InitializeImageSubsystemForPNG()
{
    return IMG_Init(IMG_INIT_PNG);
}

int InitializeImageSubsystemForJPEG()
{
    return IMG_Init(IMG_INIT_JPG);
}

int NewTexture(Texture* tex, Window* win, const char *filePath, int width, int height)
{
    Log("Loading texture '%s'...", filePath);

    SDL_Surface* textureSurface = IMG_Load(filePath);
    if (textureSurface == NULL){
        Log("Unable to load texture '%s'...", filePath);
        Log("Error message: %s", IMG_GetError());
        return 1;
    }
    
    SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(win->renderer, textureSurface);

    SDL_FreeSurface(textureSurface); // we dont need surface no more
    tex->texture = sdlTex;
    tex->width = width;
    tex->height = height;
    tex->id = ++textureID;

    return 0;
}

int NewBitmapTexture(Texture* tex, Window* win, const char *filePath, int width, int height)
{
    Log("Loading bitmap texture '%s'...", filePath);
    
    SDL_Surface* textureSurface = SDL_LoadBMP(filePath);
    if (textureSurface == NULL){
        Log("Unable to load bitmap texture '%s'...", filePath);
        return 1;
    }
    
    SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(win->renderer, textureSurface);

    SDL_FreeSurface(textureSurface); // we dont need surface no more
    tex->texture = sdlTex;
    tex->width = width;
    tex->height = height;
    tex->id = ++textureID;

    return 0;
}

Rectangle GetRectangleFromTexture(Texture *texture)
{
    return (Rectangle){ 0, 0, texture->width, texture->height };
}

void FreeTexture(Texture *texture)
{
    Log("Freeing texture... [ID: %d]", texture->id--);
    SDL_DestroyTexture(texture->texture);
}

void NewSpritesheet(Spritesheet* sheet, Texture *tex, int frameWidth, int frameHeight)
{
    sheet->col = 0;
    sheet->row = 0;
    sheet->frameHeight = frameHeight;
    sheet->frameWidth = frameWidth;
    sheet->tex = tex;
}

Rectangle GetCutoutFromSpritesheet(Spritesheet *sheet)
{
    return (Rectangle) { sheet->frameWidth * sheet->col, sheet->frameHeight * sheet->row, sheet->frameWidth, sheet->frameHeight};
}
