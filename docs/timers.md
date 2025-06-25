## Timers in core

In core, timers use the deltatime to manage time.

## Making and freeing a timer

To make a timer,
```cpp
Timer* timer = NewTimer(2.0f, true);

// 2.0f is the duration
// true is whether the timer should loop back once finished or not
```

To replace a timer safely,
```cpp
ReplaceTimer(timer, 2.5f, false);
```

To free a timer.
```cpp
FreeTimer(timer);
```


## Updating timer and getting time

To update the timer, you can simply use the `UpdateTimer(Timer*)` function.

To get the remaining time, Just do `timer.remaining`

However to get the elapsed time, You need to call the `GetElapsed(Timer*)` function.

You can also reset a timer using `ResetTimer(Timer*)`

If you just wanna check if the timer is finished or not, use `IsFinished(Timer*)`
> Sidenote: If your timer loops, then make sure to check is finished BEFORE updating the timer, otherwise when its below 0, update timer function will just reset it and prevent isfinished from returning true
