#include "core2d.h"


void NewTimer(Timer* timer, float duration, bool loop)
{
    timer->maxDuration = duration;
    timer->remaining = duration;
    timer->loop = loop;
}

void ResetTimer(Timer *timer)
{
    timer->remaining = timer->maxDuration;
}

bool IsFinished(Timer *timer)
{
    return timer->remaining <= 0.0f;
}

void UpdateTimer(Timer *timer)
{
    if (timer == NULL) return;
    
    float dt = (float) GetDeltaTime();

    timer->remaining -= dt;

    if (timer->remaining < 0.0f){
        if (timer->loop) timer->remaining = timer->maxDuration;
        else timer->remaining = 0.0f;
    }
}

float GetElapsed(Timer *timer)
{
    if (timer == NULL) return 0.0f;
    float elapsed = timer->maxDuration - timer->remaining;
    if (elapsed < 0.0f) return 0.0f;
    return elapsed;
}
