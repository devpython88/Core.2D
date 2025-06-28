#include "core2d.h"

SDL_Scancode GetScancode(Window *win)
{
    return win->event->key.keysym.scancode;
}

SDL_Keycode GetKeycode(Window *win)
{
    return win->event->key.keysym.sym;
}

bool IsKeyJustPressed(SDL_Keycode keycode)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
    return sm_scancodes[scancode] && !(sm_oldScancodes[scancode]);
}

bool IsKeyJustReleased(SDL_Keycode keycode)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
    return !(sm_scancodes[scancode]) && sm_oldScancodes[scancode];
}

bool IsKeyHeld(SDL_Keycode keycode)
{
    SDL_Scancode scancode = SDL_GetScancodeFromKey(keycode);
    return sm_scancodes[scancode];
}

bool IsMousePressed(Window *win, Uint8 button)
{
    return win->event->type == SDL_MOUSEBUTTONDOWN &&
        win->event->button.button == button;
}

Uint8 GetMousePressed(Window *win)
{
    return win->event->button.button;
}
