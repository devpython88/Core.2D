#ifndef CORE2D_H
#define CORE2D_H
#define SDL_MAIN_HANDLED

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif



// DELTA TIME
extern Uint64 TIME_NOW, TIME_LAST;








// WINDOW
typedef struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int fps;
} Window;

// COLOR
typedef struct Color {
    Uint8 r, g, b, a;
} Color;

// SHAPES
typedef struct Rectangle {
    int x, y, width, height;
} Rectangle;

typedef struct Circle {
    int x, y, radius;
} Circle;


// MATH-RELATED

typedef struct Vector2i {
    int x, y;
} Vector2i;

typedef struct Vector2f {
    float x, y;
} Vector2f;

// LOGGING

void Log(const char* format, ...);
void Err(const char* format, ...);


// WINDOW-RELATED FUNCTIONS



Window* NewWindow(const char* title, int width, int height, int fps);

bool WindowIsOpen(Window* win);

void DestroyWindow(Window* win);

void UpdateDeltaTime();
double GetDeltaTime();



// RENDER-RELATED FUNCTIONS




void RenderSetColor(Window* win, Color color);
void RenderFill(Window* win, Color color);
void RenderFillRect(Window* win, Rectangle rec, Color c);
void RenderLinesRect(Window* win, Rectangle rec, Color c);
void RenderFillCircle(Window* win, Circle circle, Color c);
void RenderDrawPoint(Window* win, int x, int y, Color c);
void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c);
void RenderShow(Window* win);









#ifdef __cplusplus
}
#endif

#endif