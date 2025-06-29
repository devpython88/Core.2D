#include "core2d.h"


Vector2f GetMomentum(Vector2f velocity, float mass)
{
    Vector2f newVec = { velocity.x, velocity.y };
    newVec.x *= mass;
    newVec.y *= mass;

    return newVec;
}

float GetKineticEnergy(Vector2f velocity, float mass)
{
    float speed = velocity.x * velocity.x + velocity.y * velocity.y;
    return mass * 0.5f * speed;
}

Vector2f GetForce(Vector2f acceleration, float mass)
{
    return (Vector2f) { acceleration.x * mass, acceleration.y * mass };
}

Vector2f GetDrag(Vector2f velocity, float dragCoefficient)
{
    return (Vector2f){
        -velocity.x * dragCoefficient,
        -velocity.y * dragCoefficient
    };
}

int Clamp(int num, int min, int max)
{
    if (num < min) return min;
    return (num > max) ? max : num;
}

double ClampEx(double num, double min, double max)
{
    if (num < min) return min;
    return (num > max) ? max : num;
}

float ClampF(float num, float min, float max)
{
    if (num < min) return min;
    return (num > max) ? max : num;
}

float GetDistance(float startX, float startY, float endX, float endY)
{
    return GetDistanceV((Vector2f){startX, startY}, (Vector2f){endX, endY});
}

float GetDistanceV(Vector2f start, Vector2f end)
{
    return fabsf((end.x - start.x) + (end.y - start.y));
}

float GetArea(float width, float height)
{
    return width * height;
}

bool AreLinesColliding(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2, Vector2f* output)
{
    float x1 = a1.x, y1 = a1.y;
    float x2 = a2.x, y2 = a2.y;
    float x3 = b1.x, y3 = b1.y;
    float x4 = b2.x, y4 = b2.y;

    float denom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
    if (fabsf(denom) < 1e-6f) return false; // lines are parallel

    float px = ((x1*y2 - y1*x2)*(x3 - x4) - (x1 - x2)*(x3*y4 - y3*x4)) / denom;
    float py = ((x1*y2 - y1*x2)*(y3 - y4) - (y1 - y2)*(x3*y4 - y3*x4)) / denom;

    // Check if the intersection is within both segments
    if (
        px < fminf(x1, x2) - 1e-4f || px > fmaxf(x1, x2) + 1e-4f ||
        py < fminf(y1, y2) - 1e-4f || py > fmaxf(y1, y2) + 1e-4f ||
        px < fminf(x3, x4) - 1e-4f || px > fmaxf(x3, x4) + 1e-4f ||
        py < fminf(y3, y4) - 1e-4f || py > fmaxf(y3, y4) + 1e-4f
    ) {
        return false;
    }

    if (output != NULL) {
        output->x = px;
        output->y = py;
    }

    return true;
}

int Minimum(int a, int b)
{
    return (a < b) ? a : b;
}

float MinimumF(float a, float b)
{
    return (a < b) ? a : b;
}

double MinimumD(double a, double b)
{
    return (a < b) ? a : b;
}

int Maximum(int a, int b)
{
    return (a > b) ? a : b;
}

float MaximumF(float a, float b)
{
    return (a > b) ? a : b;
}

double MaximumD(double a, double b)
{
    return (a > b) ? a : b;
}
