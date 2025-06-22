#include "core2d.h"

// Array of default colors, indexed by color enum
const Color defaultColors[] = {
    [RED]    = {255,   0,   0, 255},
    [GREEN]  = {  0, 255,   0, 255},
    [BLUE]   = {  0,   0, 255, 255},
    [YELLOW] = {255, 255,   0, 255},
    [PURPLE] = {128,   0, 128, 255},
    [PINK]   = {255, 192, 203, 255},
    [BLACK]  = {  0,   0,   0, 255},
    [WHITE]  = {255, 255, 255, 255},
    [BROWN]  = {139,  69,  19, 255},
    [ORANGE] = {255, 165,   0, 255},
    [CYAN]   = {  0, 255, 255, 255},
    [MAGENTA]= {255,   0, 255, 255},
    [GRAY]   = {128, 128, 128, 255}
};

// Timing variables for delta time calculation
Uint64 TIME_NOW = 0;
Uint64 TIME_LAST = 0;

// Logging function with printf-style formatting
void Log(const char *format, ...)
{
    printf("[LOG] ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);  // behaves like printf
    va_end(args);

    printf("\n");  // optional newline
}

// Error logging function with printf-style formatting
void Err(const char *format, ...)
{
    printf("[ERROR] ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);  // behaves like printf
    va_end(args);

    printf("\n");  // optional newline
}

// Create and initialize a new window and renderer
Window *NewWindow(const char *title, int width, int height, int fps)
{
    Log("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        Err("Failed to initialize SDL! Abort.");
        Log("Error message: %s", SDL_GetError());
        return NULL;
    }

    Log("Creating window...");
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window){
        Err("Failed to initialize window! Abort.");
        Log("Error message: %s", SDL_GetError());
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        Err("Failed to intialize renderer! Abort.");
        Log("Error message: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        return NULL;
    }

    SDL_Event* event = (SDL_Event*)malloc(sizeof(SDL_Event));

    Log("Finalizing window...");

    Window* cWin = (Window*)malloc(sizeof(Window));

    if (cWin == NULL){
        Err("Failed to initialize core.2d window!");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        return NULL;
    }

    cWin->window = window;
    cWin->renderer = renderer;
    cWin->fps = fps;
    cWin->event = event;

    Log("Initializing default camera...");

    Camera* cam = (Camera*)malloc(sizeof(Camera));

    if (cam == NULL){
        Err("Failed to initialize core.2d camera!");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        free(cWin);
        return NULL;
    }

    cam->targetX = 0;
    cam->targetY = 0;
    cam->zoom = 1.0f;

    currentCamera = cam;

    return cWin;
}

// Check if the window is still open (not closed by user)
bool WindowIsOpen(Window *win)
{
    // fetch event
    SDL_PollEvent(win->event);
    // window is open is called every frame and if we poll event here, that means user aint have to

    // check if its open
    return win->event->type != SDL_QUIT;
}

// Destroy window, renderer, and camera, and free memory
void DestroyWindow(Window *win)
{
    if (currentCamera != NULL){
        Log("Destroying camera...");
        free(currentCamera);
    }
    
    Log("Destroying renderer...");
    SDL_DestroyRenderer(win->renderer);

    Log("Destroying window...");
    SDL_DestroyWindow(win->window);

    Log("Freeing window...");
    free(win->event);
    free(win);
}

// Quit SDL and cleanup
void Quit()
{
    Log("Uninitializing SDL...");
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

// Update timing variables for delta time calculation
void UpdateDeltaTime() {
    TIME_LAST = TIME_NOW;
    TIME_NOW = SDL_GetPerformanceCounter();
}

// Get the time difference between frames in seconds
double GetDeltaTime() {
    return (double)(TIME_NOW - TIME_LAST) / SDL_GetPerformanceFrequency(); // in seconds
}

// Set the renderer's draw color
void RenderSetColor(Window *win, Color color)
{
    SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);
}

// Fill the window with a color, and check for camera existence
void RenderFill(Window *win, Color color)
{
    RenderSetColor(win, color);
    SDL_RenderClear(win->renderer);

    if (currentCamera == NULL){
        Err("No camera found, Aborting to avoid worst-case-scenarios.");
        DestroyWindow(win);
        Quit();
        exit(1);
    }
}

// Fill a rectangle with color, camera-relative
void RenderFillRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    
    Vector2i newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    Vector2i newSize = GetCameraRelativeSize(rec.width, rec.height);
    
    SDL_Rect sdlRec = { newPos.x, newPos.y, newSize.x, newSize.y };
    SDL_RenderFillRect(win->renderer, &sdlRec);
}

// Draw rectangle outline with color, camera-relative
void RenderLinesRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);

    Vector2i newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    Vector2i newSize = GetCameraRelativeSize(rec.width, rec.height);

    SDL_Rect sdlRec = { newPos.x, newPos.y, newSize.x, newSize.y };
    SDL_RenderDrawRect(win->renderer, &sdlRec);
}

// Draw a filled circle with color, camera-relative
void RenderFillCircle(Window *win, Circle circle, Color c)
{
    RenderSetColor(win, c);
    
    Vector2i newPos = GetCameraRelativePosition(circle.x, circle.y);
    float newRadius = GetCameraRelativeSize(circle.radius, 0).x;

    for (int dy = -newRadius; dy <= newRadius; dy++) {
        int dx = (int)sqrt(newRadius * newRadius - dy * dy);
        SDL_RenderDrawLine(
            win->renderer,
            newPos.x - dx, newPos.y + dy,
            newPos.x + dx, newPos.y + dy
        );
    }
}

// Draw a single point with color, camera-relative
void RenderDrawPoint(Window *win, int x, int y, Color c)
{
    RenderSetColor(win, c);
    Vector2i newPos = GetCameraRelativePosition(x, y);
    SDL_RenderDrawPoint(win->renderer, newPos.x, newPos.y);
}

// Draw a line between two points with color, camera-relative
void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c)
{
    RenderSetColor(win, c);

    Vector2i newStartPos = GetCameraRelativePosition(start.x, start.y);
    Vector2i newEndPos = GetCameraRelativePosition(end.x, end.y);

    SDL_RenderDrawLine(win->renderer, newStartPos.x, newStartPos.y, newEndPos.x, newEndPos.y);
}

void RenderDrawTexture(Window *win, int x, int y, Texture *texture)
{
    if (texture == NULL) return;

    Vector2i newPos = GetCameraRelativePosition(x, y);
    Vector2i newSize = GetCameraRelativeSize(texture->width, texture->height);
    const SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };

    SDL_RenderCopy(
        win->renderer,
        texture->texture, // give it the texture
        NULL, // give it a empty source rect since we dont need frames rn
        &destRec
    );
}

void RenderDrawTextureEx(Window *win, Vector2i pos, Texture *texture, Rectangle cutout)
{
    if (texture == NULL) return;

    Vector2i newPos = GetCameraRelativePosition(pos.x, pos.y);
    Vector2i newSize = GetCameraRelativeSize(texture->width, texture->height);

    SDL_Rect srcRec = { cutout.x, cutout.y, cutout.width, cutout.height };
    SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };

    SDL_RenderCopy(
        win->renderer,
        texture->texture,
        &srcRec,
        &destRec
    );
}

void RenderDrawText(Window *win, Text *text, int x, int y)
{
    Vector2i newPos = GetCameraRelativePosition(x, y);
    Vector2i newSize = GetCameraRelativeSize(text->width, text->height);

    const SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };

    SDL_RenderCopy(win->renderer,
        text->tex, NULL,
        &destRec);
}

// Present the rendered frame and delay to maintain FPS
void RenderShow(Window *win)
{
    SDL_RenderPresent(win->renderer);
    SDL_Delay(1000 / win->fps);
}
