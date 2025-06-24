#ifndef CORE2D_H
#define CORE2D_H
#define SDL_MAIN_HANDLED

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

// PREPROCESSOR MACROS

// Allocates memory for a single object of type
#define ALLOCATE(type) (type*)malloc(sizeof(type))

// Allocates memory for an array of 'size' elements of type
#define ARR_ALLOC(type, size) (type*)malloc(size * sizeof(type))

// Resizes an array to 'newsize' elements of type
#define ARR_RESIZE(arr, type, newsize) (type*)realloc(arr, newsize * sizeof(type))

// Frees memory allocated for an array
#define ARR_DESTROY(arr) free(arr)

// alias for inifnite loops
#define INF_LOOP -1

// alias to find nearest available channel

#define NEAREST_AVAILABLE_CHANNEL -1

// COLORS

// Represents an RGBA color
typedef struct Color {
    Uint8 r, g, b, a;
} Color;

// Enum for default color indices
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

// Array of default colors
extern const Color defaultColors[];

// DELTA TIME

// Stores current and last time for delta time calculation
extern Uint64 TIME_NOW, TIME_LAST;

// CAMERA

// Represents a camera with position and zoom
typedef struct Camera {
    int targetX, targetY;
    float zoom;
} Camera;

// Pointer to the current camera and camera usage flag
extern Camera* currentCamera;
extern bool useCamera;

// WINDOW

// Represents a window with SDL objects and FPS
typedef struct Window {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event* event;
    int fps;
} Window;


// SOUNDS

typedef struct Sound {
    Mix_Chunk* chunk;
} Sound;

typedef struct Music {
    Mix_Music* content;
} Music;

// TEXTURES

typedef struct Texture {
    SDL_Texture* texture;
    int width, height;
} Texture;


typedef struct Spritesheet {
    Texture* tex;
    int frameWidth, frameHeight;
    int row, col;
} Spritesheet;


// TEXT

typedef struct TextFont {
    TTF_Font* font;
} TextFont;


typedef struct Text {
    SDL_Texture* tex;
    int width;
    int height;
} Text;


// SHAPES

// Rectangle shape
typedef struct Rectangle {
    int x, y, width, height;
} Rectangle;

// Circle shape
typedef struct Circle {
    int x, y, radius;
} Circle;


// MATH-RELATED

// 2D integer vector
typedef struct Vector2i {
    int x, y;
} Vector2i;


// 2D float vector
typedef struct Vector2f {
    float x, y;
} Vector2f;

// FILE MANAGEMENT

typedef struct IoFile {
    FILE* cfile;
    char* path;
} IoFile;

// LOGGING

// Logs a formatted message
void Log(const char* format, ...);

// Logs a formatted error message
void Err(const char* format, ...);

// WINDOW-RELATED FUNCTIONS

// Creates a new window
Window* NewWindow(const char* title, int width, int height, int fps);
Window* NewWindowEx(SDL_Window* sdlW, SDL_Renderer* sdlR, SDL_Event* sdlE);

// Checks if the window is open
bool WindowIsOpen(Window* win);

// Destroys a window
void DestroyWindow(Window* win);

// Quits the application
void Quit();

// Updates delta time values
void UpdateDeltaTime();

// Gets the current delta time in seconds
double GetDeltaTime();

// CAMERA RELATED FUNCTIONS

// Gets position relative to the camera
Vector2i GetCameraRelativePosition(int x, int y);

// Gets size based on the camera zoom, Returns as-is if failed
Vector2i GetCameraRelativeSize(int w, int h);

// Enables camera usage
void EnableCamera();

// Disables camera usage
void DisableCamera();

// Frees the current camera
void FreeCamera();

// Sets a new camera
void SetCamera(Camera* newCam);

// RENDER-RELATED FUNCTIONS

// Sets the renderer color
void RenderSetColor(Window* win, Color color);

// Fills the window with a color
void RenderFill(Window* win, Color color);

// Fills a rectangle with a color
void RenderFillRect(Window* win, Rectangle rec, Color c);

// Draws rectangle lines
void RenderLinesRect(Window* win, Rectangle rec, Color c);

// Fills a circle with a color
void RenderFillCircle(Window* win, Circle circle, Color c);

// Draws a point
void RenderDrawPoint(Window* win, int x, int y, Color c);

// Draws a line between two points
void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c);

// Draws a entire texture
void RenderDrawTexture(Window* win, int x, int y, Texture* texture);

// Draw a cutout
void RenderDrawTextureEx(Window* win, Vector2i pos, Texture* texture, Rectangle cutout);

// Draw a cutout + more
void RenderDrawTexturePro(Window* win, Vector2i pos, Texture* texture, Rectangle cutout, Vector2i origin, int angle, SDL_RendererFlip flip);

// Draw a spritesheet
void RenderDrawSpritesheet(Window* win, int x, int y, Spritesheet* sheet);

// Draw text
void RenderDrawText(Window* win, Text* text, int x, int y);

// Presents the rendered frame
void RenderShow(Window* win);


// COLLISION-RELATED FUNCTIONS


// check rectangle to rectangle collision
bool CheckCollisionAABB(int x1, int y1, int w1, int h1,
    int x2, int y2, int w2, int h2);

// check circle to ectangle collision
bool CheckCollisionCircleRec(int x1, int y1, int r1, int x2, int y2, int w2, int h2);

// INPUT-RELATED FUNCTIONS

extern Vector2i mousePosition;
extern Vector2i mouseScroll;

// Gets the current scancode from input
SDL_Scancode GetScancode(Window* win);

// Gets the current keycode from input
SDL_Keycode GetKeycode(Window* win);

// Returns whether that key was pressed
bool IsKeyPressed(Window* win, SDL_Keycode keycode);

// Returns whether that mouse button was pressed
bool IsMousePressed(Window* win, Uint8 button);

// Returns the pressed mouse button or NULL if no button pressed
Uint8 GetMousePressed(Window* win);



// TEXTURE-RELATED FUNCTIONS

int InitializeImageSubsystemForPNG();
int InitializeImageSubsystemForJPEG();

Texture* NewTexture(Window* win, const char* filePath, int width, int height);
Texture* NewBitmapTexture(Window* win, const char* filePath, int width, int height);

Rectangle GetRectangleFromTexture(Texture* texture);

void FreeTexture(Texture* texture);

// SPRITESHEET RELATED

Spritesheet* NewSpritesheet(Texture* tex, int frameWidth, int frameHeight);
void FreeSpritesheet(Spritesheet* sheet);
Rectangle GetCutoutFromSpritesheet(Spritesheet* sheet);

// Font-RELATED FUNCTIONS

// Initialize font susbsystem, returns 0 on success
int InitializeFontSubsystem();

// Initialize a text font, returns null on fail
TextFont* NewTextFont(const char* path, int fontSize);

// Initialize text, returns null on fail
Text* NewText(Window* win, TextFont* font, const char* text, Color color);
Text* NewTextEx(Window* win, TextFont* font, const char* text, Color color, bool blend);

// Free stuff
void FreeText(Text* text);
void FreeTextFont(TextFont* font);


// SOUND-RELATED

int InitializeSFXSubsystem(int frequency, Uint16 format, int channels, int chunksize);
int InitializeSFXFor(int format);

Music* NewMusicStream(const char* path);
Sound* NewSound(const char* path);

void FreeMusicStream(Music* music);
void FreeSound(Sound* sound);

void PlayMusicStream(Music* music, int loops);
bool PlayingMusic();
void PauseMusic();
void ResumeMusic();

void PlaySound(Sound* sound, int channel, int loops);


// FILE-RELATED

// Opens a file, Returns NULL if failed
IoFile* OpenFile(const char* path, const char* mode);

// Appends to a file
void FileAppend(IoFile* file, const char* text);

// Returns file size
long GetFileSize(IoFile* file);

// Returns current cursor pos or -1 on error
long GetFileCursorPos(IoFile* file);

// Closes and frees a file
void CloseFile(IoFile* file);

// Seeks the cursor at `to` in `file`
void FileSeek(IoFile* file, int origin);
void FileSeekEx(IoFile* file, int offset, int origin);

// Rewinds cursor to start in file
void FileRewind(IoFile* file);

// Returns file content or null on fail
char* FileRead(IoFile* file);

// quick writes to a file, returns 0 on succes, 1 on fail
int QuickFileWrite(const char* path, const char* text);

// reads file, returns null if failed
char* QuickFileRead(const char* path);



#ifdef __cplusplus
}
#endif

#endif