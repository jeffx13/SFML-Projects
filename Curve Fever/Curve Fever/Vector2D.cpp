#include "Vector2D.h"
# define PI 3.14159265358979323846

Vector2D::Vector2D()
{
    this->x = 0;
    this->y = 0;
    this->radius = 0;
}

Vector2D::Vector2D(float x, float y)
{
    this->x = x;
    this->y = y;
}
Vector2D::Vector2D(float x, float y,float radius)
{
    Vector2D(x, y);
    this->radius = radius;
}

Vector2D Vector2D::operator+(const Vector2D& other) const
{
    return Vector2D( x + other.x, y + other.y );
}

void Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;
}

Vector2D Vector2D::operator-(const Vector2D& other) const
{
    return *this+(- other);
}

Vector2D Vector2D::operator-() const
{
    return Vector2D(-x, -y);
}

void Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
}

Vector2D Vector2D::operator*(const float other) const
{
    return Vector2D(x*other,y* other);
}

void Vector2D::operator*=(const float other) 
{
    x *= other;
    y *= other;
}

Vector2D Vector2D::operator/(const float other) const
{
    return Vector2D(x/other,y/other);
}

void Vector2D::operator/=(const float other) 
{
    x /= other;
    y /= other;
}

void Vector2D::rotate(float angle)
{
    x = cos((angle* PI) / 180) * x - sin((angle * PI) / 180) * y;
    y = sin((angle * PI) / 180) * x + cos((angle * PI) / 180) * y;
}

float Vector2D::GetDistance(Vector2D other)
{
    return std::sqrtf((other.y - y) * (other.y - y) + (other.x - x) * (other.x - x));
}

float Vector2D::GetMagnitude()
{
    return std::sqrtf(x * x + y * y);
}

Vector2D Vector2D::GetNormalised()
{
    return Vector2D(x/GetMagnitude(),y/GetMagnitude());
}

void Vector2D::Normalise()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
}

Vector2D Vector2D::PerpendicularClockwise()
{
    return Vector2D(y, -x);
}

Vector2D Vector2D::FindVector(Vector2D other)
{
    return Vector2D(other.x-x,other.y-y);
}

Vector2D Vector2D::PerpendicularAntiClockwise()
{
    return Vector2D(-y, x);
}

std::ostream& operator<<(std::ostream& os, const Vector2D& vector)
{
    os << "(" << vector.x << ", " << vector.y << ")";
    return os;
}
