#include "core2d.h"

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
    SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    if (!window || !renderer){
        Err("Failed to create window! Abort.");
        return NULL;
    }

    SDL_Event event;

    Log("Finalizing window...");

    Window* cWin = (Window*)malloc(sizeof(Window));
    cWin->window = window;
    cWin->renderer = renderer;
    cWin->fps = fps;
    cWin->event = event;

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
    Log("Destroying renderer...");
    SDL_DestroyRenderer(win->renderer);

    Log("Destroying window...");
    SDL_DestroyWindow(win->window);
    
    Log("Uninitializing SDL...");
    SDL_Quit();
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
}

void RenderFillRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    SDL_Rect sdlRec = { rec.x, rec.y, rec.width, rec.height };
    SDL_RenderFillRect(win->renderer, &sdlRec);
}

void RenderLinesRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    SDL_Rect sdlRec = { rec.x, rec.y, rec.width, rec.height };
    SDL_RenderDrawRect(win->renderer, &sdlRec);
}

void RenderFillCircle(Window *win, Circle circle, Color c)
{
    for (int dy = -circle.radius; dy <= circle.radius; dy++) {
        int dx = (int)sqrt(circle.radius * circle.radius - dy * dy);
        SDL_RenderDrawLine(win->renderer, circle.x - dx, circle.y + dy, circle.x + dx, circle.y + dy);
    }
}

void RenderDrawPoint(Window *win, int x, int y, Color c)
{
    RenderSetColor(win, c);
    SDL_RenderDrawPoint(win->renderer, x, y);
}

void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c)
{
    RenderSetColor(win, c);
    SDL_RenderDrawLine(win->renderer, start.x, start.y, end.x, end.y);
}

void RenderShow(Window *win)
{
    SDL_RenderPresent(win->renderer);
    SDL_Delay(1000 / win->fps);
}
