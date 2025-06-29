#include "core2d.h"

Uint8 sm_scancodes[MAX_SCANCODES] = { 0 };
Uint8 sm_oldScancodes[MAX_SCANCODES] = { 0 };

int textureID = 0;

char** errors = NULL;
int count = -1; // -1 so when we push it auto becomes 0

Uint64 TIME_NOW = 0;
Uint64 TIME_LAST = 0;

Vector2f mousePosition = { 0, 0 };
Vector2f mouseScroll = { 0, 0 };

// Array of default colors, indexed by color enum

void PushError(const char *format, ...)
{
    if (errors == NULL) return;

    // allocate TEMP space for a new string
    char** tmp = (char**)realloc(errors, sizeof(errors) + sizeof(char*));

    // handle error
    if (tmp == NULL){
        Err("Could not push string to errors array.");
        return;
    }

    // Format the string

    char* formattedString;

    va_list args;
    va_start(args, format);
    vsprintf(formattedString, format, args);
    va_end(args);

    tmp[count++] = formattedString;

    errors = tmp;
}

char *GetLastError()
{
    if (errors == NULL) return "";

    return errors[count];
}

char **GetAllErrors()
{
    return errors;
}

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

void InitializeCore2D()
{
    errors = (char**)malloc(sizeof(char*));
    errors[0] = NULL;
}

// Create and initialize a new window and renderer
int NewWindow(Window* window, const char *title, int width, int height, int fps)
{
    
    Log("Initializing SDL...");
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
        Err("Failed to initialize SDL! Abort.");
        PushError("Failed to initialize SDL! Abort.");
        Log("Error message: %s", SDL_GetError());
        return 1;
    }

    Log("Creating window...");
    SDL_Window* swindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (!window){
        Err("Failed to initialize window! Abort.");
        PushError("Failed to initialize window! Abort.");
        Log("Error message: %s", SDL_GetError());
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(swindow, 0, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        Err("Failed to intialize renderer! Abort.");
        PushError("Failed to intialize renderer! Abort.");
        Log("Error message: %s", SDL_GetError());
        SDL_DestroyWindow(swindow);
        return 1;
    }
    
    SDL_Event* event = (SDL_Event*)malloc(sizeof(SDL_Event));
    
    Log("Finalizing window...");
    
    window->window = swindow;
    window->renderer = renderer;
    window->fps = fps;
    window->event = event;
    
    Log("Initializing default camera...");
    
    Camera* cam = (Camera*)malloc(sizeof(Camera));
    
    if (cam == NULL){
        Err("Failed to initialize core.2d camera!");
        PushError("Failed to initialize core.2d camera!");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(swindow);
        return 1;
    }

    cam->targetX = 0;
    cam->targetY = 0;
    cam->zoom = 1.0f;
    
    currentCamera = cam;
    
    TIME_NOW = SDL_GetPerformanceCounter();
    TIME_LAST = TIME_NOW;
    
    return 0;
}

int NewWindowEx(Window* window, SDL_Window *sdlW, SDL_Renderer *sdlR, SDL_Event *sdlE)
{
    window->renderer = sdlR;
    window->event = sdlE;
    window->window = sdlW;
    window->fps = 60;
    return 0;
}

int FetchEvents(Window *win)
{
    // update scancodes
    UpdateScancodes();

    return SDL_PollEvent(win->event);
}

bool IsEvent(Window *win, int type)
{
    return win->event->type == type;
}

SDL_Event* GetEvent(Window *win)
{
    return win->event;
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
}

// Quit SDL and cleanup
void Quit()
{
    Log("Uninitializing SDL...");
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
    Mix_Quit();
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
        PushError("No camera found, Aborting to avoid worst-case-scenarios.");
        DestroyWindow(win);
        Quit();
        exit(1);
    }
}

// Fill a rectangle with color, camera-relative
void RenderFillRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);
    
    Vector2f newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    Vector2f newSize = GetCameraRelativeSize(rec.width, rec.height);
    
    SDL_Rect sdlRec = { newPos.x, newPos.y, newSize.x, newSize.y };
    SDL_RenderFillRect(win->renderer, &sdlRec);
}

// Draw rectangle outline with color, camera-relative
void RenderLinesRect(Window *win, Rectangle rec, Color c)
{
    RenderSetColor(win, c);

    Vector2f newPos = GetCameraRelativePosition(rec.x, rec.y); // No handling required since if theres no camera, it will just return the x and y
    Vector2f newSize = GetCameraRelativeSize(rec.width, rec.height);

    SDL_Rect sdlRec = { newPos.x, newPos.y, newSize.x, newSize.y };
    SDL_RenderDrawRect(win->renderer, &sdlRec);
}

// Draw a filled circle with color, camera-relative
void RenderFillCircle(Window *win, Circle circle, Color c)
{
    RenderSetColor(win, c);
    
    Vector2f newPos = GetCameraRelativePosition(circle.x, circle.y);
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
void RenderDrawPoint(Window *win, float x, float y, Color c)
{
    RenderSetColor(win, c);
    Vector2f newPos = GetCameraRelativePosition(x, y);
    SDL_RenderDrawPoint(win->renderer, newPos.x, newPos.y);
}

// Draw a line between two points with color, camera-relative
void RenderDrawLine(Window* win, Vector2f start, Vector2f end, Color c)
{
    RenderSetColor(win, c);

    Vector2f newStartPos = GetCameraRelativePosition(start.x, start.y);
    Vector2f newEndPos = GetCameraRelativePosition(end.x, end.y);

    SDL_RenderDrawLine(win->renderer, newStartPos.x, newStartPos.y, newEndPos.x, newEndPos.y);
}

void RenderDrawTexture(Window *win, float x, float y, Texture *texture)
{
    if (texture == NULL) return;

    Vector2f newPos = GetCameraRelativePosition(x, y);
    Vector2f newSize = GetCameraRelativeSize(texture->width, texture->height);
    const SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };

    SDL_RenderCopy(
        win->renderer,
        texture->texture, // give it the texture
        NULL, // give it a empty source rect since we dont need frames rn
        &destRec
    );
}

void RenderDrawTextureEx(Window *win, Vector2f pos, Texture *texture, Rectangle cutout)
{
    if (texture == NULL) return;

    Vector2f newPos = GetCameraRelativePosition(pos.x, pos.y);
    Vector2f newSize = GetCameraRelativeSize(texture->width, texture->height);

    SDL_Rect srcRec = { cutout.x, cutout.y, cutout.width, cutout.height };
    SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };

    SDL_RenderCopy(
        win->renderer,
        texture->texture,
        &srcRec,
        &destRec
    );
}

void RenderDrawTexturePro(Window * win, Vector2f pos, Texture * texture, Rectangle cutout, Vector2f origin, int angle, SDL_RendererFlip flip)
{
    if (texture == NULL) return;

    Vector2f newPos = GetCameraRelativePosition(pos.x, pos.y);
    Vector2f newSize = GetCameraRelativeSize(texture->width, texture->height);

    SDL_Rect srcRec = { cutout.x, cutout.y, cutout.width, cutout.height };
    SDL_Rect destRec = { newPos.x, newPos.y, newSize.x, newSize.y };
    
    SDL_RenderCopyEx(
        win->renderer,
        texture->texture,
        &srcRec, &destRec,
        (double) angle,
        &((SDL_Point) { origin.x, origin.y }),
        flip
    );
}

void RenderDrawSpritesheet(Window *win, float x, float y, Spritesheet *sheet)
{
    RenderDrawTextureEx(
        win,
        (Vector2f) { x, y },
        sheet->tex,
        (Rectangle){ sheet->col * sheet->frameWidth, sheet->row * sheet->frameHeight, sheet->frameWidth, sheet->frameHeight }
    );
}

void RenderDrawText(Window *win, Text *text, float x, float y)
{
    Vector2f newPos = GetCameraRelativePosition(x, y);
    Vector2f newSize = GetCameraRelativeSize(text->width, text->height);

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

bool CheckCollisionAABB(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
    return (
        x1 < x2 + w2 &&
        y1 < y2 + h2 &&
        x1 + w1 > x2 &&
        y1 + h1 > y2
    );
}

bool CheckCollisionCircleRec(float x1, float y1, float r1, float x2, float y2, float w2, float h2)
{
    // Find the closest point on the rectangle to the circle center
    int closestX = fmax(x2, fmin(x1, x2 + w2));
    int closestY = fmax(y2, fmin(y1, y2 + h2));

    // Calculate the distance between the circle's center and this closest point
    int dx = x1 - closestX;
    int dy = y1 - closestY;

    // If the distance is less than the circle's radius, they are colliding
    return (dx * dx + dy * dy) <= (r1 * r1);
}



// SCANCODES

void UpdateScancodes()
{
    CopyScancodesToOld();

    int numberOfKeys;
    const Uint8 *keyboard = SDL_GetKeyboardState(&numberOfKeys);

    // if number of keys is less than max, then the limit is the number of keys
    // else its the max scancodes

    int limit = (numberOfKeys < MAX_SCANCODES) ? numberOfKeys : MAX_SCANCODES;

    // copy keyboard to scancode array
    for (int i = 0; i < limit; i++){
        sm_scancodes[i] = (keyboard[i] == 1);
    }
}

void CopyScancodesToOld()
{
    for (int i = 0; i < MAX_SCANCODES; i++){
        sm_oldScancodes[i] = sm_scancodes[i];
    }
}


void MoveTowards(float *x, float *y, float dstX, float dstY, float speed)
{
    float stop = MinimumF(1.0f, speed);
    MoveTowardsEx(x, y, dstX, dstY, speed, stop);
}

void MoveTowardsEx(float *x, float *y, float dstX, float dstY, float speed, float stopDistance)
{
    float distance = GetDistance(*x, *y, dstX, dstY);

    if (distance < stopDistance) return;

    float deltaX = 0.0f;
    float deltaY = 0.0f;

    if (*x < dstX) deltaX += speed;
    if (*y < dstY) deltaY += speed;
    if (*x > dstX) deltaX -= speed;
    if (*y > dstY) deltaY -= speed;

    *x += deltaX;
    *y += deltaY;
}
