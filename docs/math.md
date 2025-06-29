## This is just a cheatsheet for c2d_math

### Physics
`Vector2f GetMomentum(Vector2f velocity, float mass)`
- Returns the momentum using velocity and mass

`float GetKineticEnergy(Vector2f velocity, float mass)`
- Returns the kinetic energy using velocity and masss

`Vector2f GetForce(Vector2f acceleration, float mass)`
- Returns the force using acceleration and mass

`Vector2f GetDrag(Vector2f velocity, float dragCoefficient)`
- Returns the amount of drag using velocity and a drag coefficient


### Math
`int Clamp(int num, int min, int max)`
- Clamps a value to a min and max

`double ClampEx(double num, double min, double max)`
- Clamp but for doubles

`float ClampF(float num, float min, float max)`
- Clamp but for floats

`float GetDistance(float startX, float startY, float endX, float endY)`
- Returns the distance, Which is `fabsf(startx - endx + starty - endy)`

`float GetDistanceV(Vector2f start, Vector2f end)`
- Same as above but using vectors

`float GetArea(float width, float height)`
- Returns width multiplied by height

`bool AreLinesColliding(Vector2f a1, Vector2f a2, Vector2f b1, Vector2f b2, Vector2f* output)`
- Returns whether the lines collide, And if the `output` parameter isn't `NULL`, Then it writes the exact position they collided in that vector.

`int Minimum(int a, int b)`
- Get the smallest number

`float MinimumF(float a, float b)`
- Minimum but for floats

`double MinimumD(double a, double b)`
- Minimum but for doubles

`int Maximum(int a, int b)`
- Get the largest number

`float MaximumF(float a, float b)`
- Maximum for floats

`double MaximumD(double a, double b)`
- Maximum for doubles
