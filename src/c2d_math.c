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
