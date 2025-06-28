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
 * @return The position relative to the camera as a Vector2f
 */
Vector2f GetCameraRelativePosition(float x, float y)
{
    if (!useCamera || currentCamera == NULL) return (Vector2f){x, y};

    float relX = (float)((x - currentCamera->targetX) * currentCamera->zoom);
    float relY = (float)((y - currentCamera->targetY) * currentCamera->zoom);
    return (Vector2f){ relX, relY };
}

// Get size and position relative to camera (with zoom and offset)
Vector2f GetCameraRelativeSize(float w, float h)
{
    if (currentCamera == NULL || !useCamera) return (Vector2f) { w, h };

    // The size is scaled by zoom, but you may want to also provide a function for position
    return (Vector2f){ (float)(w * currentCamera->zoom), (float)(h * currentCamera->zoom) };
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
