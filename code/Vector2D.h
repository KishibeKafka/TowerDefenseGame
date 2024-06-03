#pragma once
#include <cmath>
#include <graphics.h>
#include <ostream>

#define PPU 64.0

class Vector2D
{
public:
    double x, y;
    Vector2D() : x(0), y(0) {}
    Vector2D(double a, double b) : x(a), y(b) {}
    // 计算两个坐标的直线距离
    static double Distance(const Vector2D &a, const Vector2D &b)
    {
        return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    }
    // 将一个坐标绕原点旋转一定角度得到新坐标
    static Vector2D Rotate(double angle, const Vector2D &another)
    {
        double radian = PI * angle / 180;
        double dsin = sin(radian);
        double dcos = cos(radian);
        return Vector2D(another.x * dcos - another.y * dsin,
                        another.x * dsin + another.y * dcos);
    }
    static double getAngle(const Vector2D &a, const Vector2D &b)
    {
        Vector2D delta(b.x - a.x, b.y - a.y);
        double angle = std::atan2(delta.y, delta.x);
        angle = angle * 180 / PI;
        if (angle < 0)
            angle += 360;
        return angle;
    }
    Vector2D operator+(const Vector2D &another)
    {
        return Vector2D(x + another.x, y + another.y);
    }
    Vector2D operator*(const Vector2D &another)
    {
        return Vector2D(x * another.x, y * another.y);
    }
    Vector2D operator-()
    {
        return Vector2D(-x, -y);
    }
    Vector2D &operator=(const Vector2D &another)
    {
        if (this == &another)
            return *this;
        x = another.x;
        y = another.y;
        return *this;
    }
    Vector2D &operator+=(const Vector2D &another)
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
    bool operator==(const Vector2D &another)
    {
        return x == another.x && y == another.y;
    }
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v)
    {
        os << '(' << v.x << ',' << v.y << ')';
        return os;
    }
};