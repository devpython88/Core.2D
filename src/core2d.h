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
#include <math.h>

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

// max scancodes
#define MAX_SCANCODES SDL_NUM_SCANCODES


// ERROR MANAGEMENT
extern char** errors; // This is a resizable array btw
extern int count;


void PushError(const char* format, ...);
char* GetLastError();
char** GetAllErrors();



// COLORS

// Represents an RGBA color
typedef struct Color {
    Uint8 r, g, b, a;
} Color;

// Colors

#define RED     (Color){255,   0,   0, 255}
#define GREEN   (Color){  0, 255,   0, 255}
#define BLUE    (Color){  0,   0, 255, 255}
#define YELLOW  (Color){255, 255,   0, 255}
#define PURPLE  (Color){128,   0, 128, 255}
#define PINK    (Color){255, 192, 203, 255}
#define BLACK   (Color){  0,   0,   0, 255}
#define WHITE   (Color){255, 255, 255, 255}
#define BROWN   (Color){139,  69,  19, 255}
#define ORANGE  (Color){255, 165,   0, 255}
#define CYAN    (Color){  0, 255, 255, 255}
#define MAGENTA (Color){255,   0, 255, 255}
#define GRAY    (Color){128, 128, 128, 255}

// Texture id
extern int textureID;


// SCANCODE MANAGER

extern Uint8 sm_scancodes[MAX_SCANCODES];
extern Uint8 sm_oldScancodes[MAX_SCANCODES];

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
    float width, height;
    int id;
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
    float width;
    float height;
} Text;


// SHAPES

// Rectangle shape
typedef struct Rectangle {
    float x, y, width, height;
} Rectangle;

// Circle shape
typedef struct Circle {
    float x, y, radius;
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


// TIMER

typedef struct Timer {
    float maxDuration;
    float remaining;
    bool loop;
} Timer;

// LOGGING

// Logs a formatted message
void Log(const char* format, ...);

// Logs a formatted error message
void Err(const char* format, ...);

// WINDOW-RELATED FUNCTIONS

void InitializeCore2D();

// Creates a new window returns 1 if failed
int NewWindow(Window* window, const char* title, int width, int height, int fps);
int NewWindowEx(Window* window, SDL_Window* sdlW, SDL_Renderer* sdlR, SDL_Event* sdlE);

// Fetch events
int FetchEvents(Window* win);

// Check if event is
bool IsEvent(Window* win, int type);

// Get event
SDL_Event* GetEvent(Window* win);

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
Vector2f GetCameraRelativePosition(float x, float y);

// Gets size based on the camera zoom, Returns as-is if failed
Vector2f GetCameraRelativeSize(float w, float h);

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
void RenderDrawPoint(Window* win, float x, float y, Color c);

// Draws a line between two points
void RenderDrawLine(Window* win, Vector2f start, Vector2f end, Color c);

// Draws a entire texture
void RenderDrawTexture(Window* win, float x, float y, Texture* texture);

// Draw a cutout
void RenderDrawTextureEx(Window* win, Vector2f pos, Texture* texture, Rectangle cutout);

// Draw a cutout + more
void RenderDrawTexturePro(Window* win, Vector2f pos, Texture* texture, Rectangle cutout, Vector2f origin, int angle, SDL_RendererFlip flip);

// Draw a spritesheet
void RenderDrawSpritesheet(Window* win, float x, float y, Spritesheet* sheet);

// Draw text
void RenderDrawText(Window* win, Text* text, float x, float y);

// Presents the rendered frame
void RenderShow(Window* win);


// COLLISION-RELATED FUNCTIONS


// check rectangle to rectangle collision
bool CheckCollisionAABB(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2);

// check circle to ectangle collision
bool CheckCollisionCircleRec(float x1, float y1, float r1, float x2, float y2, float w2, float h2);

// INPUT-RELATED FUNCTIONS

extern Vector2f mousePosition;
extern Vector2f mouseScroll;

// Gets the current scancode from input
SDL_Scancode GetScancode(Window* win);

// Gets the current keycode from input
SDL_Keycode GetKeycode(Window* win);

// Returns whether key wasn't pressed but is pressed now
bool IsKeyJustPressed(SDL_Keycode keycode);

// Returns whether the key is just released
bool IsKeyJustReleased(SDL_Keycode keycode);

// Returns whether the key was held
bool IsKeyHeld(SDL_Keycode keycode);

// Returns whether that mouse button was pressed
bool IsMousePressed(Window* win, Uint8 button);

// Returns the pressed mouse button or NULL if no button pressed
Uint8 GetMousePressed(Window* win);



// TEXTURE-RELATED FUNCTIONS

int InitializeImageSubsystemForPNG();
int InitializeImageSubsystemForJPEG();

// returns 1 if failed
int NewTexture(Texture* tex, Window* win, const char* filePath, float width, float height);
int NewBitmapTexture(Texture* tex, Window* win, const char* filePath, float width, float height);

Rectangle GetRectangleFromTexture(Texture* texture);

void FreeTexture(Texture* texture);

// SPRITESHEET RELATED

void NewSpritesheet(Spritesheet* sheet, Texture* tex, int frameWidth, int frameHeight);
Rectangle GetCutoutFromSpritesheet(Spritesheet* sheet);

// Font-RELATED FUNCTIONS

// Initialize font susbsystem, returns 0 on success
int InitializeFontSubsystem();

// Initialize a text font, returns 1 on fail
int NewTextFont(TextFont* font, const char* path, int fontSize);

// Initialize text, returns 1 on fail
int NewText(Text* out, Window* win, TextFont* font, const char* text, Color color);
int NewTextEx(Text* out, Window* win, TextFont* font, const char* text, Color color, bool blend);

// Free stuff
void FreeTextFont(TextFont* font);
void FreeText(Text* text);


// SOUND-RELATED

int InitializeSFXSubsystem(int frequency, Uint16 format, int channels, int chunksize);
int InitializeSFXFor(int format);

int NewMusicStream(Music* out, const char* path);
int NewSound(Sound* out, const char* path);

void FreeMusicStream(Music* music);
void FreeSound(Sound* sound);

void PlayMusicStream(Music* music, int loops);
bool PlayingMusic();
void PauseMusic();
void ResumeMusic();

void PlaySound(Sound* sound, int channel, int loops);


// FILE-RELATED

// Opens a file, Returns 1 if failed
int OpenFile(IoFile* file, const char* path, const char* mode);

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


// TIMER RELATED

// Makes a new timer, doesnt fail
void NewTimer(Timer* timer, float duration, bool loop);

// Reset timer.
void ResetTimer(Timer* timer);

// Returns if timer is finished
bool IsFinished(Timer* timer);

// Updates timer
void UpdateTimer(Timer* timer);

// Returns elapsed time
float GetElapsed(Timer* timer);


// MATH RELATED FUNCS

Vector2f GetMomentum(Vector2f velocity, float mass);
float GetKineticEnergy(Vector2f velocity, float mass);
Vector2f GetForce(Vector2f acceleration, float mass);
Vector2f GetDrag(Vector2f velocity, float dragCoefficient);
int Clamp(int num, int min, int max);
double ClampEx(double num, double min, double max);
float ClampF(float num, float min, float max);
float GetDistance(float startX, float startY, float endX, float endY);
float GetDistanceV(Vector2f start, Vector2f end);
float GetArea(float width, float height);
bool AreLinesColliding(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2, Vector2f* output);
int Minimum(int a, int b);
float MinimumF(float a, float b);
double MinimumD(double a, double b);
int Maximum(int a, int b);
float MaximumF(float a, float b);
double MaximumD(double a, double b);

// SCANCODE RELATED

void UpdateScancodes();
void CopyScancodesToOld();


// MOVEMENT-RELATED

void MoveTowards(float* x, float* y, float dstX, float dstY, float speed);
void MoveTowardsEx(float* x, float* y, float dstX,
    float dstY, float speed, float stopDistance);

#ifdef __cplusplus
}
#endif

#endif