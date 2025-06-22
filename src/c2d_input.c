#include "core2d.h"

SDL_Scancode GetScancode(Window *win)
{
    return win->event->key.keysym.scancode;
}

SDL_Keycode GetKeycode(Window *win)
{
    return win->event->key.keysym.sym;
}

bool IsKeyPressed(Window *win, SDL_Keycode keycode)
{
    return win->event->type == SDL_KEYDOWN
        && GetKeycode(win) == keycode;
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
