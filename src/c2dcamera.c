#include "core2d.h"


bool useCamera = true;
Camera* currentCamera = NULL;


Vector2i GetCameraRelativePosition(float x, float y)
{
    if (!useCamera) return (Vector2i){x, y};

    if (currentCamera == NULL){
        Err("No camera found");
        return (Vector2i){x, y};
    }

    return (Vector2i){x - currentCamera->targetX, y - currentCamera->targetY};
}

void EnableCamera()
{
    useCamera = true;
}

void DisableCamera()
{
    useCamera = false;
}

void FreeCamera()
{
    if (currentCamera != NULL){
        free(currentCamera);
        currentCamera = NULL;
    }
}

void SetCamera(Camera *newCam)
{
    FreeCamera();
    currentCamera = newCam;
}
