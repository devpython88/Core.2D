# Core.2D
Core is a replacement for my old game library (nova.h), It is made in C which means its not OOP but I am dedicating myself to make this library a good library and not buggy like my previous game library


Core is built ontop of SDL2 and adds many features that SDL2 doesn't have (for ex. Camera) Here is a example of loading a texture:

```cpp
#include "core2d.h"

int main() {
    Window* win = NewWindow("Hello world.", 800, 600, 60);

    Texture* ball = NewTexture(win, "ball.png", 50, 50); // file path, scaled width, scaled height

    while (WindowIsOpen(win)){
        RenderFill(win, defaultColors[WHITE]);
        RenderDrawTexture(win, 100, 0, ball); // Draw the whole texture
        RenderDrawTextureEx(win, (Vector2i) { 0, 0 }, ball, (Rectangle) { 0, 0, 8, 8 } ); // Draw a cutout from the texture
        RenderShow(win);
    }

    FreeTexture(ball); // free the texture
    DestroyWindow(win);
    Quit();
    return 0;
}
```




### Setting up nova
If you use MSYS2 or Linux then you can simply download the prebuilt-x64-binaries

However if you use a different system then you have to use a different approach.

1. Clone the repository
`git clone https://github.com/devpython88/core.2d.git`

2. Install these dependencies

You need to install the following dependencies:
SDL2, SDL2_image, SDL2_ttf, SDL2_mixer

3. Run `configure`

For windows:
`configure.bat dist X Y`

Replace `X` with whatever generator you use, If the generator name has  spaces then put the name in double-quotes

Replace `Y` with the executable for your generator (ex. make for Unix Makefiles)

For UNIX (macOS, Linux):

`configure.sh dist X Y no`

Same as above.
