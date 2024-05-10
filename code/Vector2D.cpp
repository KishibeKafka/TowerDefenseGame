#include "Vector2D.h"
#include <iostream>

Vector2D Vector2D::Rotate(double angle, const Vector2D &another)
{
    double radian = PI * angle / 180;
    double dsin = sin(radian);
    double dcos = cos(radian);
    return Vector2D(another.x * dcos - another.y * dsin,
                    another.x * dsin + another.y * dcos);
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

std::ostream &operator<<(std::ostream &os, Vector2D &v)
{
    os << '(' << v.x << ',' << v.y << ')';
    return os;
}

void test()
{
    Vector2D A(3, 4);
    Vector2D O;
    Vector2D B(-1, -2);
    std::cout << Vector2D::Distance(A, O) << '\n';
    Vector2D C = Vector2D::Rotate(90, A);
    std::cout << C << '\n';
    Vector2D D = B + C;
    std::cout << D << '\n';
    D = -D;
    std::cout << D << '\n';
}