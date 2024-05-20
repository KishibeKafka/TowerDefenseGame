#include "Vector2D.h"
#include <cmath>
#include <iostream>

Vector2D Vector2D::Rotate(double angle, const Vector2D &another)
{
    double radian = PI * angle / 180;
    double dsin = sin(radian);
    double dcos = cos(radian);
    return Vector2D(another.x * dcos - another.y * dsin,
                    another.x * dsin + another.y * dcos);
}

double Vector2D::getAngle(const Vector2D &a, const Vector2D &b)
{
    Vector2D delta(b.x - a.x, b.y - a.y);
    double angle = std::atan2(delta.y, delta.x);
    angle = angle * 180 / PI;
    if (angle < 0)
        angle += 360;
    return angle;
}

Vector2D Vector2D::operator+(const Vector2D &another)
{
    return Vector2D(x + another.x, y + another.y);
}

Vector2D Vector2D::operator*(const Vector2D &another)
{
    return Vector2D(x * another.x, y * another.y);
}

Vector2D Vector2D::operator-()
{
    return Vector2D(-x, -y);
}

Vector2D &Vector2D::operator=(const Vector2D &another)
{
    if (this == &another)
        return *this;
    x = another.x;
    y = another.y;
    return *this;
}

Vector2D &Vector2D::operator+=(const Vector2D &another)
{
    if (this == &another)
    {
        x *= 2;
        y *= 2;
        return *this;
    }
    x += another.x;
    y += another.y;
    return *this;
}

bool Vector2D::operator==(const Vector2D &another)
{
    return x == another.x && y == another.y;
}

std::ostream &operator<<(std::ostream &os, const Vector2D &v)
{
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}

void test()
{
    Vector2D O;
    Vector2D A(1, 1);
    Vector2D B(-1, 1);
    Vector2D C(-1, -1);
    Vector2D D(1, -1);
    std::cout << "OA :" << Vector2D::getAngle(O, A) << '\n';
    std::cout << "OB :" << Vector2D::getAngle(O, B) << '\n';
    std::cout << "OC :" << Vector2D::getAngle(O, C) << '\n';
    std::cout << "OD :" << Vector2D::getAngle(O, D) << '\n';
}