#include "core2d.h"

int InitializeImageSubsystemForPNG()
{
    return IMG_Init(IMG_INIT_PNG);
}

int InitializeImageSubsystemForJPEG()
{
    return IMG_Init(IMG_INIT_JPG);
}

Texture *NewTexture(Window* win, const char *filePath, int width, int height)
{
    Log("Loading texture '%s'...", filePath);
    Texture* texture = (Texture*)malloc(sizeof(Texture));

    SDL_Surface* textureSurface = IMG_Load(filePath);
    if (textureSurface == NULL){
        Log("Unable to load texture '%s'...", filePath);
        Log("Error message: %s", IMG_GetError());
        return NULL;
    }
    
    SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(win->renderer, textureSurface);

    SDL_FreeSurface(textureSurface); // we dont need surface no more
    texture->texture = sdlTex;
    texture->width = width;
    texture->height = height;

    return texture;
}

Texture *NewBitmapTexture(Window* win, const char *filePath, int width, int height)
{
    Log("Loading bitmap texture '%s'...", filePath);
    Texture* texture = (Texture*)malloc(sizeof(Texture));

    SDL_Surface* textureSurface = SDL_LoadBMP(filePath);
    if (textureSurface == NULL){
        Log("Unable to load bitmap texture '%s'...", filePath);
        return NULL;
    }
    
    SDL_Texture* sdlTex = SDL_CreateTextureFromSurface(win->renderer, textureSurface);

    SDL_FreeSurface(textureSurface); // we dont need surface no more
    texture->texture = sdlTex;
    texture->width = width;
    texture->height = height;

    return texture;
}

void FreeTexture(Texture *texture)
{
    SDL_DestroyTexture(texture->texture);
    free(texture);
}

Spritesheet *NewSpritesheet(Texture *tex, int frameWidth, int frameHeight)
{
    Spritesheet* sheet = (Spritesheet*)malloc(sizeof(Spritesheet));
    sheet->col = 0;
    sheet->row = 0;
    sheet->frameHeight = frameHeight;
    sheet->frameWidth = frameWidth;
    sheet->tex = tex;

    return sheet;
}

void FreeSpritesheet(Spritesheet *sheet)
{
    free(sheet);
}
