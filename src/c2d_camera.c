#include "core2d.h"

// Global flag to determine if the camera should be used
bool useCamera = true;

// Pointer to the current active camera
Camera* currentCamera = NULL;

/**
 * Returns the position relative to the camera's target.
 * If the camera is disabled or not set, returns the original position.
 *
 * @param x The x coordinate in world space
 * @param y The y coordinate in world space
 * @return The position relative to the camera as a Vector2i
 */
Vector2i GetCameraRelativePosition(int x, int y)
{
    if (!useCamera || currentCamera == NULL) return (Vector2i){x, y};

    int relX = (int)((x - currentCamera->targetX) * currentCamera->zoom);
    int relY = (int)((y - currentCamera->targetY) * currentCamera->zoom);
    return (Vector2i){ relX, relY };
}

// Get size and position relative to camera (with zoom and offset)
Vector2i GetCameraRelativeSize(int w, int h)
{
    if (currentCamera == NULL || !useCamera) return (Vector2i) { w, h };

    // The size is scaled by zoom, but you may want to also provide a function for position
    return (Vector2i){ (int)(w * currentCamera->zoom), (int)(h * currentCamera->zoom) };
}

/**
 * Enables camera usage for position calculations.
 */
void EnableCamera()
{
    useCamera = true;
}

/**
 * Disables camera usage for position calculations.
 */
void DisableCamera()
{
    useCamera = false;
}

/**
 * Frees the memory allocated for the current camera and sets it to NULL.
 */
void FreeCamera()
{
    if (currentCamera != NULL){
        free(currentCamera);
        currentCamera = NULL;
    }
}

/**
 * Sets a new camera as the current camera.
 * Frees the previous camera if it exists.
 *
 * @param newCam Pointer to the new Camera to set
 */
void SetCamera(Camera *newCam)
{
    FreeCamera();
    currentCamera = newCam;
}
