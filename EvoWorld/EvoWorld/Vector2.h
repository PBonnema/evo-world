#pragma once
#include <cmath>
#include <algorithm>

template <typename T>
struct Vector2
{
public:
    constexpr Vector2(T x, T y) :
        x_{x},
        y_{y}
    {
    }

    constexpr Vector2(const Vector2& other) = default;
    constexpr Vector2& operator=(const Vector2& other) = default;

    [[nodiscard]] constexpr Vector2 operator+(const Vector2& other) const
    {
        return {x_ + other.x_, y_ + other.y_};
    }

    [[nodiscard]] constexpr Vector2 operator-(const Vector2& other) const
    {
        return {x_ - other.x_, y_ - other.y_};
    }

    template <typename U>
    [[nodiscard]] constexpr Vector2 operator*(U scalar) const
    {
        return {x_ * scalar, y_ * scalar};
    }

    template <typename U>
    [[nodiscard]] constexpr Vector2 operator/(U scalar) const
    {
        return {x_ / scalar, y_ / scalar};
    }

    constexpr Vector2& operator+=(const Vector2& other)
    {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    constexpr Vector2& operator-=(const Vector2& other)
    {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    template <typename U>
    constexpr Vector2& operator*=(U scalar)
    {
        x_ *= scalar;
        y_ *= scalar;
        return *this;
    }

    template <typename U>
    constexpr Vector2& operator/=(U scalar)
    {
        x_ /= scalar;
        y_ /= scalar;
        return *this;
    }

    [[nodiscard]] constexpr bool operator==(const Vector2& other) const
    {
        return x_ == other.x_ && y_ == other.y_;
    }

    [[nodiscard]] constexpr bool operator!=(const Vector2& other) const
    {
        return x_ != other.x_ || y_ != other.y_;
    }

    [[nodiscard]] constexpr T get_x() const
    {
        return x_;
    }

    [[nodiscard]] constexpr T get_y() const
    {
        return y_;
    }

    constexpr void set_x(T new_x)
    {
        x_ = new_x;
    }

    constexpr void set_y(T new_y)
    {
        y_ = new_y;
    }

    constexpr void set(T new_x, T new_y)
    {
        x_ = new_x;
        y_ = new_y;
    }

    template <typename U = T>
    [[nodiscard]] constexpr Vector2<U> get_normalized() const
    {
        double length = get_length();
        if (length != 0.0)
            return *this / length;
        return *this;
    }

    [[nodiscard]] constexpr double get_length() const
    {
        return std::sqrt(x_ * x_ + y_ * y_);
    }

    [[nodiscard]] constexpr T get_length_squared() const
    {
        return x_ * x_ + y_ * y_;
    }

    [[nodiscard]] constexpr double get_angle() const
    {
        return std::atan2(y_, x_);
    }

    [[nodiscard]] constexpr double dot(const Vector2& other) const
    {
        return x_ * other.x_ + y_ * other.y_;
    }

    [[nodiscard]] constexpr Vector2 get_perpendicular() const
    {
        return {-y_, x_};
    }

    [[nodiscard]] constexpr Vector2 get_rotated(T angle) const
    {
        T s = std::sin(angle);
        T c = std::cos(angle);
        return {x_ * c - y_ * s, x_ * s + y_ * c};
    }

    [[nodiscard]] constexpr Vector2 get_reflected(const Vector2& normal) const
    {
        return *this - normal * 2 * dot(normal);
    }

    [[nodiscard]] constexpr Vector2 get_projected(const Vector2& axis) const
    {
        return axis * dot(axis) / axis.get_length_squared();
    }

    [[nodiscard]] constexpr static double distance(const Vector2& v1, const Vector2& v2)
    {
        return (v1 - v2).getLength();
    }

    [[nodiscard]] constexpr static double distance_squared(const Vector2& v1, const Vector2& v2)
    {
        return (v1 - v2).get_length_squared();
    }

    [[nodiscard]] constexpr static Vector2 lerp(const Vector2& v1, const Vector2& v2, T t)
    {
        return v1 + (v2 - v1) * t;
    }

    [[nodiscard]] constexpr static Vector2 from_polar(const double angle, const double length = 1.0)
    {
        return {std::cos(angle) * length, std::sin(angle) * length};
    }

    [[nodiscard]] constexpr static Vector2 from_polar(const Vector2& v)
    {
        return from_polar(v.x_, v.y_);
    }

    [[nodiscard]] constexpr static double angle(const Vector2& v1, const Vector2& v2)
    {
        return std::atan2(v2.y_, v2.x_) - std::atan2(v1.y_, v1.x_);
    }

    [[nodiscard]] constexpr static double angle_between(const Vector2& v1, const Vector2& v2)
    {
        return acos(std::clamp(v1.dot(v2), -1.0, 1.0));
    }

    [[nodiscard]] constexpr static double signed_angle(const Vector2& v1, const Vector2& v2)
    {
        return std::atan2(v2.y_, v2.x_) - std::atan2(v1.y_, v1.x_);
    }

    [[nodiscard]] constexpr static double signed_angle_between(const Vector2& v1, const Vector2& v2)
    {
        return std::acos(std::clamp(v1.dot(v2), -1.0, 1.0));
    }

    [[nodiscard]] constexpr static double cross_product(const Vector2& v1, const Vector2& v2)
    {
        return v1.x_ * v2.y_ - v1.y_ * v2.x_;
    }

    [[nodiscard]] constexpr static Vector2 min(const Vector2& v1, const Vector2& v2)
    {
        return {std::min(v1.x_, v2.x_), std::min(v1.y_, v2.y_)};
    }

    [[nodiscard]] constexpr static Vector2 max(const Vector2& v1, const Vector2& v2)
    {
        return {std::max(v1.x_, v2.x_), std::max(v1.y_, v2.y_)};
    }

    [[nodiscard]] constexpr static Vector2 floor(const Vector2& v)
    {
        return {std::floor(v.x_), std::floor(v.y_)};
    }

    [[nodiscard]] constexpr static Vector2 ceil(const Vector2& v)
    {
        return {std::ceil(v.x_), std::ceil(v.y_)};
    }

    [[nodiscard]] constexpr static Vector2 round(const Vector2& v)
    {
        return {std::round(v.x_), std::round(v.y_)};
    }

    [[nodiscard]] constexpr static Vector2 abs(const Vector2& v)
    {
        return {std::abs(v.x_), std::abs(v.y_)};
    }

    [[nodiscard]] constexpr static Vector2 clamp(const Vector2& v, const Vector2& min, const Vector2& max)
    {
        return {std::clamp(v.x_, min.x_, max.x_), std::clamp(v.y_, min.y_, max.y_)};
    }

    [[nodiscard]] constexpr static Vector2 clamp(const Vector2& v, T min, T max)
    {
        return {std::clamp(v.x_, min, max), std::clamp(v.y_, min, max)};
    }

private:
    T x_;
    T y_;
};
