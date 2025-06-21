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
    
// PREPROCESSER MACROS

#define ALLOCATE(type) (type*)malloc(sizeof(type))
#define ARR_ALLOC(type, size) (type*)malloc(size * sizeof(type))
#define ARR_RESIZE(arr, type, newsize) (type*)realloc(arr, newsize * sizeof(type))
#define ARR_DESTROY(arr) free(arr)



// COLORS

typedef struct Color {
    Uint8 r, g, b, a;
} Color;

enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    PINK,
    BLACK,
    WHITE,
    BROWN,
    ORANGE,
    CYAN,
    MAGENTA,
    GRAY
};

extern const Color defaultColors[];



// DELTA TIME
extern Uint64 TIME_NOW, TIME_LAST;







// CAMERA

typedef struct Camera {
    int targetX, targetY;
    float zoom;
} Camera;

extern Camera* currentCamera;
extern bool useCamera;



// WINDOW
typedef struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    int fps;
} Window;


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
void Quit();

void UpdateDeltaTime();
double GetDeltaTime();




// CAMERA RELATED FUNCTIONS


Vector2i GetCameraRelativePosition(float x, float y);
void EnableCamera();
void DisableCamera();
void FreeCamera();
void SetCamera(Camera* newCam);

// RENDER-RELATED FUNCTIONS




void RenderSetColor(Window* win, Color color);
void RenderFill(Window* win, Color color);
void RenderFillRect(Window* win, Rectangle rec, Color c);
void RenderLinesRect(Window* win, Rectangle rec, Color c);
void RenderFillCircle(Window* win, Circle circle, Color c);
void RenderDrawPoint(Window* win, int x, int y, Color c);
void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c);
void RenderShow(Window* win);





// INPUT-RELATED FUNCTIONS

SDL_Scancode GetScancode(Window* win);
SDL_Keycode GetKeycode(Window* win);





#ifdef __cplusplus
}
#endif

#endif