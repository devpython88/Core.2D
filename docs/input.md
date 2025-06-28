# Input in Core.2D (core for short)

in core, Input is mostly the same as sdl except for the fact that its polled automatically when you check if the window is open.

## key and mouse presses

There are many different ways to check input in core

1. Key Input
To check if a key was held: `IsKeyHeld(SDL_Keycode)`
To check if a key was just pressed: `IsKeyJustPressed(SDL_Keycode)`
To check if a key was just released: `IsKeyJustReleased(SDL_Keycode)`

2. Mouse input
To check if a mouse button is pressed: `IsMousePressed(button)`

3. Getting keycode and scancode
To get the pressed key: `GetKeycode(Window*)`
To get the pressed scancode: `GetScancode(Window*)`

## Mouse position

To get the mouse position, You can use the global `Vector2i mousePosition`.
And to get the scroll, you can use the global `Vector2i mouseScroll`.

## How to get more event info
To get more event info, you can simply access the `SDL_Event* event` variable in the `Window` struct.


## Delta time
You can use `GetDeltaTime` to get the delta time.
Make sure to call `UpdateDeltaTime` every frame.