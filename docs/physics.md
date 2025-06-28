## Physics Helpers

Core.2D includes lightweight physics helper functions to assist with basic physical calculations like momentum, kinetic energy, force, and drag. These are ideal for quick simulations or arcade-style physics without the need for a full physics engine.

These functions use the `Vector2f` struct, which holds two `float` values: `x` and `y`.

### `Vector2f GetMomentum(Vector2f velocity, float mass)`

Returns the **momentum** vector of an object using the formula:
`momentum = velocity * mass`

```cpp
Vector2f momentum = GetMomentum((Vector2f){2.0f, 3.0f}, 5.0f);
// Result: {10.0f, 15.0f}
```

### `float GetKineticEnergy(Vector2f velocity, float mass)`

Returns the **kinetic energy** of an object using the formula:
`KE = 0.5 * mass * (velocity.x² + velocity.y²)`

```cpp
float ke = GetKineticEnergy((Vector2f){3.0f, 4.0f}, 2.0f);
// Result: 0.5 * 2 * (9 + 16) = 25.0
```

### `Vector2f GetForce(Vector2f acceleration, float mass)`

Returns the **force** vector applied to an object using Newton's second law:
`force = acceleration * mass`

```cpp
Vector2f force = GetForce((Vector2f){1.0f, 2.0f}, 3.0f);
// Result: {3.0f, 6.0f}
```

### `Vector2f GetDrag(Vector2f velocity, float dragCoefficient)`

Returns a **drag force** vector opposing the direction of motion, proportional to velocity:
`drag = -velocity * dragCoefficient`

```cpp
Vector2f drag = GetDrag((Vector2f){5.0f, -2.0f}, 0.1f);
// Result: {-0.5f, 0.2f}
```

---

These functions can be freely combined and used within your game loop or entity logic. Here's an example of combining them to simulate basic movement with drag:

```cpp
Vector2f velocity = { 3.0f, 0.0f };
float mass = 1.0f;
float dragCoef = 0.1f;

Vector2f dragForce = GetDrag(velocity, dragCoef);
Vector2f momentum = GetMomentum(velocity, mass);
float energy = GetKineticEnergy(velocity, mass);
```