# Input in Core.2D (core for short)

in core, Input is mostly the same as sdl except for the fact that its polled automatically when you check if the window is open.

## Simple key and mouse presses

To check simple key pressed in SDL2 you have two options
1. Use `IsKeyPressed(Window* win, SDL_Keycode key)`
- If you use this, Then you wont have to check if the event was `KEYDOWN`

2. Use `GetKeycode(Window* win)` or `GetScancode(Window* win)`
- These provide more control since they don't auto-handle if the event was `KEYDOWN`

Same goes for mouse buttons, There is `IsMousePressed(Window* win, Uint8 button)` function and a `GetMousePressed(Window* win)` function.

## Mouse position

To get the mouse position, You can use the global `Vector2i mousePosition`.
And to get the scroll, you can use the global `Vector2i mouseScroll`.

## How to get more event info
To get more event info, you can simply access the `SDL_Event* event` variable in the `Window` struct.
