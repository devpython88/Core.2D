# Basics of Core.2D

Core.2D or core for short is a game development library built on-top of SDL2.
It aims to be as user-friendly as Raylib but still have the perfomance and integration of SDL2.

## Creating a basic window
1. Make a `Window*` object
```cpp
Window window; 
int r = NewWindow(&window, "My Window", 640, 480, 60) // (title, width, height, fps)
// Always make sure to handle errors
if (r == 1) return 1;
```

2. Make a simple game loop.
```cpp
bool running = true;

while (running){
    UpdateDeltatime(); // Do this before ANYTHING 
    for (FetchEvents(&win)){
        if (IsEvent(&win, SDL_QUIT)){
            running = false; // exit on close
        }
    }

    // Fill the renderer with white
    RenderFill(&window, WHITE);

    // Draw stuff
    RenderFillRect(&window, (Rectangle) { 0, 0, 50, 50 }, BLUE);

    // Show drawn contents
    RenderShow(&window);
}
```

3. Destroy window and quit
```cpp
DestroyWindow(&window);
Quit();
```


That is it, Developers coming from raylib might get raylib-vibes since the syntax IS inspired by raylib.


-----------------------------------


## Textures
Loading textures is also really simple, Since core handles surfaces and freeing behind the scenes, You don't have to do much

### 1. Initialize the image subsystem
```cpp
if (InitializeImageSubsystemForPNG() != 0){
    return 1; // escape when error
}

// you can also use `InitializeImageSubsystemForJPEG`
```

2. Load the texture
```cpp
Texture player;
int r = NewTexture(&player, "player.png", 100, 100); // (file, scaleWidth, scaleHeight)
// You can also use `NewBitmapTexture` for bitmaps
// handle eror
if (r == 1) return 1;
```

3. Draw the texture
```cpp
RenderDrawTexture(&window, x, y, &player);
```

4. (Bonus) Draw a cutout
Cutouts are essential for frame based animations.
```cpp
RenderDrawTextureEx(&window, (Vector2i) { x, y }, &texture, (Rectangle) { frameX, frameY, frameWidth, frameHeight });
```

5. Unload the texture
```cpp
FreeTexture(&texture);
```


## Spritesheets

Spritesheets are simple structs that abstract the calculations needed for frame-based animation

To create a spritesheet, follow these steps (Make sure you [initialize the subsystem](#1-initialize-the-image-subsystem))
1. Make a instance
```cpp
Spritesheet sheet;
NewSpritesheet(&sheet, &yourTexture, frameWidth, frameHeight);
// spritesheets arent actual textures so they dont have fails
```

2. Modify row and col
```cpp
sheet.row++;
sheet.col++;
```

3. Draw
```cpp
RenderDrawSpritesheet(&window, &sheet, x, y);
```

4. Free
```cpp
FreeTexture(&yourTexture);
```


## Rotation, Origin, Flipping
To do all of that, You have to use the `RenderDrawTexturePro` function.
Signature: `(Window* win, Vector2i pos, Texture* texture, Rectangle cutout, Vector2i origin, int angle, SDL_RendererFlip flip)`

Example:
```cpp
RenderDrawTexturePro(&win,
            Vector2i{20, 20},
            &ballTex, // Texture
            GetRectangleFromTexture(ballTex), // Cutout
            Vector2i{0, 0}, // Origin
            45, // Angle
            SDL_FLIP_NONE // Flip
            );
```

To use this on spritesheets, Simply replace the `Texture` argument with `yourSpritesheet.tex`

And replace the `Cutout` argument with `GetCutoutFromSpritesheet(yourSheet)`. 


## Integration
If you want to integrate core into your SDL2 project. But don't know what to do when core needs a `Window`

Well, to make a window by using your existing SDL2 variables, Use `NewWindowEx`

```cpp
Window win;
int r = NewWindowEx(&win, sdlWindow, sdlRenderer, sdlEvent) // make sure all are pointers or just add `&`

if (r == 1) return 1;
```

Make sure to free the window at the end
```cpp
free(win);
free(currentCamera); // Camera is added by default in core
```


## Cheatsheat

Structs for shapes:

`Rectangle`:

`int x, int y`: Position

`int width, int height`: Size



`Circle`:

`int x, int y`: Position

`int radius`: Radius

Structs for math:

`Vector2i`:

`int x, y`: Values

`Vector2f`:

`float x, y`: Values


Draw functions:

`void RenderSetColor(Window* win, Color color)`: Change the render draw color

`void RenderFill(Window* win, Color color)`: Fill the screen

`void RenderFillRect(Window* win, Rectangle rec, Color c)`: Draw a filled rectangle

`void RenderLinesRect(Window* win, Rectangle rec, Color c)`: Draw a outlined rectangle

`void RenderFillCircle(Window* win, Circle circle, Color c)`: Draw a filled circle

`void RenderDrawPoint(Window* win, int x, int y, Color c)`: Draw a point

`void RenderDrawLine(Window* win, Vector2i start, Vector2i end, Color c)`: Draw a line

`void RenderDrawTexture(Window* win, int x, int y, Texture* texture)`: Draw a texture

`void RenderDrawTextureEx(Window* win, Vector2i pos, Texture* texture, Rectangle cutout)`: Draw a cutout from a texture (the cutout rect's position and size are relative to the texture, so think of it as a frame rect)

`void RenderShow(Window* win)`: Show the drawn contents

Camera:
Core auto-inits and enables a camera on startup, To access it, you can use the `currentCamera` pointer.


`Vector2i GetCameraRelativePosition(int x, int y)`: Get position relative to camera, returns the exact position if failed

`Vector2i GetCameraRelativeSize(int w, int h)`: Get size based on camera zoom, Use with the previous function since otherwise it wont look like zooming

`void EnableCamera()`: Enable camera

`void DisableCamera()`: Disable camera

`void FreeCamera()`: Uninit camera

`void SetCamera(Camera* newCam)`: Set new camera

Collisiion:

`bool CheckCollisionAABB(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)`: check bounding box collision

`bool CheckCollisionCircleRec(int x1, int y1, int r1, int x2, int y2, int w2, int h2)`: check circle rec collision




## Error handling
Most functions in core return `NULL` or `1` on fail.
But to get the actual error message, Use the `GetLastError()` function or the `GetAllErrors()` function.
