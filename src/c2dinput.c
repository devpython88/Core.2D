#include "core2d.h"

SDL_Scancode GetScancode(Window *win)
{
    return win->event.key.keysym.scancode;
}

SDL_Keycode GetKeycode(Window *win)
{
    return win->event.key.keysym.sym;
}
