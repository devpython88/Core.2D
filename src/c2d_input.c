/**
 * @file c2dinput.c
 * @brief Input handling functions for core2d.
 */

/**
 * @brief Retrieves the SDL scancode from the given window's event.
 *
 * This function extracts the scancode from the most recent keyboard event
 * associated with the specified window.
 *
 * @param win Pointer to the Window structure containing the event data.
 * @return SDL_Scancode The scancode of the key event.
 */
 
/**
 * @brief Retrieves the SDL keycode from the given window's event.
 *
 * This function extracts the keycode (SDL_Keycode) from the most recent
 * keyboard event associated with the specified window.
 *
 * @param win Pointer to the Window structure containing the event data.
 * @return SDL_Keycode The keycode of the key event.
 */
#include "core2d.h"

SDL_Scancode GetScancode(Window *win)
{
    return win->event.key.keysym.scancode;
}

SDL_Keycode GetKeycode(Window *win)
{
    return win->event.key.keysym.sym;
}
