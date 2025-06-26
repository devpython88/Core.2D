# Text rendering in core.2d
In core.2d or core for short, Text rendering is simple since core abstracts all the surface handling and stuff behind simple functions.

## Rendering a basic text
Neither SDL or core come with pre-packaged fonts so make sure you have a `.ttf` font file availiable

1. Initialize font subsystem
```cpp
if (InitializeFontSubsystem() != 0){
    // handle error
    return 1;
}
```

2. Initialize a TextFont
```cpp
// Even though we provide a font size, we can still scale it when we render text
TextFont font;
int r = NewTextFont("<replace-with-your-font>.ttf", 30);

if (r == 1) return 1;
```

3. Make some text
```cpp
Text text;
int r = NewText(&window, &font, "Hello world!", defaultColors[BLACK]);
if (r == 1) return 1;

text.width = 100; // Optional: Scale the text
```

4. Draw the text
```cpp
RenderDrawText(&window, &text, 20, 20)
```

5. Unload everything
```cpp
FreeText(text);
FreeTextFont(font);
```




You might've noticed the font looks really choppy, That's because when the pixels end from the text, it hard cuts to the next pixel color instead of blending

To make the text blend, Use `DrawTextEx` and put a `true` at the end to tell the program to make a blended text

> Note: whenever you change the text, you must remake the text by freeing it then doing a new text
