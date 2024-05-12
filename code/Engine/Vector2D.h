#pragma once
#include <cmath>
#include <ostream>

#define PI 3.14159265358979323846

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
    static Vector2D Rotate(double angle, const Vector2D &another);

    Vector2D operator+(const Vector2D &another);
    Vector2D operator*(const Vector2D &another);
    Vector2D operator-();
    Vector2D &operator=(const Vector2D &another);
    Vector2D &operator+=(const Vector2D &another);
    bool operator==(const Vector2D &another);
    friend std::ostream &operator<<(std::ostream &os, const Vector2D &v);
};