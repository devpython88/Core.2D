#include "core2d.h"

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

Uint64 TIME_NOW = 0;
Uint64 TIME_LAST = 0;

void Log(const char *format, ...)
{
    printf("[LOG] ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);  // behaves like printf
    va_end(args);

    printf("\n");  // optional newline
}

void Err(const char *format, ...)
{
    printf("[ERROR] ");

    va_list args;
    va_start(args, format);
    vprintf(format, args);  // behaves like printf
    va_end(args);

    printf("\n");  // optional newline
}

Window *NewWindow(const char *title, int width, int height, int fps)
{
    Log("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        Err("Failed to initialize SDL! Abort.");
        return NULL;
    }

    Log("Creating window...");
    
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    
    if (!window){
        Err("Failed to initialize window! Abort.");
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    if (!renderer){
        Err("Failed to intialize renderer! Abort.");
        return NULL;
    }

    SDL_Event event;

    Log("Finalizing window...");

    Window* cWin = (Window*)malloc(sizeof(Window));
    cWin->window = window;
    cWin->renderer = renderer;
    cWin->fps = fps;
    cWin->event = event;

    Log("Initializing default camera...");

    Camera* cam = (Camera*)malloc(sizeof(Camera));
    cam->targetX = 0;
    cam->targetY = 0;
    cam->zoom = 1.0f;

    currentCamera = cam;

    return cWin;
}

bool WindowIsOpen(Window *win)
{
    // fetch event
    SDL_PollEvent(&win->event);
    // window is open is called every frame and if we poll event here, that means user aint have to

    // check if its open
    return win->event.type != SDL_QUIT;
}

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
    free(win);
}

void Quit()
{
    Log("Uninitializing SDL...");
    if (SDL_WasInit(SDL_INIT_VIDEO)) SDL_Quit();
}

void UpdateDeltaTime() {
    TIME_LAST = TIME_NOW;
    TIME_NOW = SDL_GetPerformanceCounter();
}

double GetDeltaTime() {
    return (double)(TIME_NOW - TIME_LAST) / SDL_GetPerformanceFrequency(); // in seconds
}

void RenderSetColor(Window *win, Color color)
{
    SDL_SetRenderDrawColor(win->renderer, color.r, color.g, color.b, color.a);
}

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

void RenderFillRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    Vector2i newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    SDL_Rect sdlRec = { newPos.x, newPos.y, rec.width, rec.height };
    SDL_RenderFillRect(win->renderer, &sdlRec);
}
void RenderLinesRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    Vector2i newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    SDL_Rect sdlRec = { newPos.x, newPos.y, rec.width, rec.height };
    SDL_RenderDrawRect(win->renderer, &sdlRec);
}

void RenderFillCircle(Window *win, Circle circle, Color c)
{
    RenderSetColor(win, c);
    Vector2i newPos = GetCameraRelativePosition(circle.x, circle.y);
    for (int dy = -circle.radius; dy <= circle.radius; dy++) {
        int dx = (int)sqrt(circle.radius * circle.radius - dy * dy);
        SDL_RenderDrawLine(
            win->renderer,
            newPos.x - dx, newPos.y + dy,
            newPos.x + dx, newPos.y + dy
        );
    }
}

void RenderDrawPoint(Window *win, int x, int y, Color c)
{
    RenderSetColor(win, c);
    Vector2i newPos = GetCameraRelativePosition(x, y);
    SDL_RenderDrawPoint(win->renderer, newPos.x, newPos.y);
}

void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c)
{
    RenderSetColor(win, c);

    Vector2i newStartPos = GetCameraRelativePosition(start.x, start.y);
    Vector2i newEndPos = GetCameraRelativePosition(end.x, end.y);

    SDL_RenderDrawLine(win->renderer, newStartPos.x, newStartPos.y, newEndPos.x, newEndPos.y);
}

void RenderShow(Window *win)
{
    SDL_RenderPresent(win->renderer);
    SDL_Delay(1000 / win->fps);
}
