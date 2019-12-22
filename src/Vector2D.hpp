#ifndef VECTOR2D
#define VECTOR2D

class Vector2D
{
  public:
    Vector2D();
    Vector2D(double aX, double aY);

    void operator=(const Vector2D& aVector);
    bool operator==(const Vector2D& aVector);

    Vector2D operator+(const Vector2D& aVector);
    Vector2D operator-(const Vector2D& aVector);
    void operator+=(const Vector2D& aVector);
    void operator-=(const Vector2D& aVector);

    Vector2D operator*(const Vector2D& aVector);
    Vector2D operator*(double aFactor);

    double x;
    double y;
};

#endif
