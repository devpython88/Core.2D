#include "core2d.h"


Timer *NewTimer(float duration, bool loop)
{
    Timer* timer = (Timer*)malloc(sizeof(Timer));
    if (timer == NULL){
        Err("Failed to allocate timer.");
        return NULL;
    }

    timer->maxDuration = duration;
    timer->remaining = duration;
    timer->loop = loop;

    return timer;
}

void FreeTimer(Timer *timer)
{
    free(timer);
}

void ReplaceTimer(Timer *timer, float newDuration, bool loop)
{
    timer->maxDuration = newDuration;
    timer->remaining = newDuration;
    timer->loop = loop;
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

    if (timer->remaining < 0.0f && timer->loop){
        timer->remaining = timer->maxDuration;
    }
}

float GetElapsed(Timer *timer)
{
    if (timer == NULL) return 0.0f;
    return timer->maxDuration - timer->remaining;
}
