# Basics of Core.2D

Core.2D or core for short is a game development library built on-top of SDL2.
It aims to be as user-friendly as Raylib but still have the perfomance and integration of SDL2.

## Creating a basic window
1. Make a `Window*` object
```cpp
Window* window = NewWindow("My Window", 640, 480, 60) // (title, width, height, fps)
// Always make sure to handle errors
if (window == NULL) return 1;
```

2. Make a simple game loop.
```cpp
// Loop runs while window is open
while (WindowIsOpen(window)){
    // Events are auto-polled

    // Fill the renderer with white
    RenderFill(window, defaultColors[RED]);

    // Draw stuff
    RenderFillRect(window, (Rectangle) { 0, 0, 50, 50 }, defaultColors[BLUE]);

    // Show drawn contents
    RenderShow(window);
}
```

3. Destroy window and quit
```cpp
DestroyWindow(window);
Quit():
```


That is it, Developers coming from raylib might get raylib-vibes since the syntax IS inspired by raylib.


-----------------------------------


## Textures
Loading textures is also really simple, Since core handles surfaces and freeing behind the scenes, You don't have to do much

1. Initialize the image subsystem
```cpp
if (InitializeImageSubsystemForPNG() != 0){
    return 1; // escape when error
}

// you can also use `InitializeImageSubsystemForJPEG`
```

2. Load the texture
```cpp
Texture* player = NewTexture("player.png", 100, 100); // (file, scaleWidth, scaleHeight)
// You can also use `NewBitmapTexture` for bitmaps
```

3. Draw the texture
```cpp
RenderDrawTexture(window, x, y, texture);
```

4. (Bonus) Draw a cutout
Cutouts are essential for frame based animations.
```cpp
RenderDrawTextureEx(window, (Vector2i) { x, y }, texture, (Rectangle) { frameX, frameY, frameWidth, frameHeight });
```

5. Unload the texture
```cpp
FreeTexture(texture)
```


## Cheatsheat for Shapes

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
