#pragma once
#include <cmath>
#include <algorithm>
#include <cassert>
#include <ostream>

template <typename T>
struct Vector2
{
public:
    constexpr Vector2(T x = {}, T y = {}) :
        x_{x},
        y_{y}
    {
    }

    ~Vector2() = default;

    constexpr Vector2(const Vector2& other) = default;
    constexpr Vector2(Vector2&& other) = default;
    constexpr Vector2& operator=(const Vector2& other) = default;
    constexpr Vector2& operator=(Vector2&& other) = default;

    friend std::ostream& operator<<(std::ostream& lhs, const Vector2& rhs)
    {
        return lhs << '(' << rhs.x_ << ", " << rhs.y_ << ')';
    }

    [[nodiscard]] constexpr Vector2 operator-() const
    {
        return {-x_, -y_};
    }

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
        if (scalar != 0.0)
            return {x_ / scalar, y_ / scalar};
        return *this;
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
        if (scalar != 0.0)
        {
            x_ /= scalar;
            y_ /= scalar;
        }
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

    [[nodiscard]] constexpr T x() const
    {
        return x_;
    }

    [[nodiscard]] constexpr T y() const
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
        return *this / get_length();
    }

    [[nodiscard]] constexpr double get_length() const
    {
        return std::sqrt(get_length_squared());
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

    // [[nodiscard]] constexpr Vector2 get_reflected(const Vector2& normal) const
    // {
    //     assert(normal.get_length_squared() != 0.0);
    //     return *this - normal * 2 * dot(normal); // TODO unclear what the operator precedence is here
    // }

    [[nodiscard]] constexpr Vector2 get_projected(const Vector2& axis) const
    {
        assert(axis.get_length_squared() != 0.0);
        return axis * (dot(axis) / axis.get_length_squared());
    }

    [[nodiscard]] constexpr Vector2 get_clamped(const Vector2& min, const Vector2& max) const
    {
        return {std::clamp(x_, min.x_, max.x_), std::clamp(y_, min.y_, max.y_)};
    }

    [[nodiscard]] constexpr Vector2 get_clamped(T min, T max) const
    {
        return {std::clamp(x_, min, max), std::clamp(y_, min, max)};
    }

    [[nodiscard]] constexpr Vector2 get_clamped_by_length(T min, T max) const
    {
        assert(min <= max);
        assert(min >= 0.0);
        const double length_squared = get_length_squared();
        assert(length_squared > 0.0);
        if (length_squared < min * min)
            return *this * min / std::sqrt(length_squared);
        if (length_squared > max * max)
            return *this * max / std::sqrt(length_squared);
        return *this;
    }

    [[nodiscard]] constexpr double distance(const Vector2& other) const
    {
        return (*this - other).get_length();
    }

    [[nodiscard]] constexpr double distance_squared(const Vector2& other) const
    {
        return (*this - other).get_length_squared();
    }

    [[nodiscard]] constexpr double angle(const Vector2& other) const
    {
        return std::atan2(other.y_, other.x_) - std::atan2(this->y_, this->x_);
    }

    [[nodiscard]] constexpr double angle_between(const Vector2& other) const
    {
        return std::acos(std::clamp(this->dot(other), -1.0, 1.0));
    }

    [[nodiscard]] constexpr double signed_angle(const Vector2& other) const
    {
        return std::atan2(other.y_, other.x_) - std::atan2(this->y_, this->x_);
    }

    [[nodiscard]] constexpr double signed_angle_between(const Vector2& other) const
    {
        return std::acos(std::clamp(this->dot(other), -1.0, 1.0));
    }

    [[nodiscard]] constexpr double cross_product(const Vector2& other) const
    {
        return this->x_ * other.y_ - this->y_ * other.x_;
    }

    [[nodiscard]] constexpr Vector2 to_polar() const
    {
        return polar_from_cartesian(x_, y_);
    }

    [[nodiscard]] constexpr Vector2 to_cartesian() const
    {
        return cartesian_from_polar(x_, y_);
    }

    // Static

    [[nodiscard]] constexpr static Vector2 lerp(const Vector2& v1, const Vector2& v2, double t)
    {
        return v1 + (v2 - v1) * t;
    }

    [[nodiscard]] constexpr static Vector2 cartesian_from_polar(const double angle, const double r = 1.0)
    {
        return {std::cos(angle) * r, std::sin(angle) * r};
    }

    [[nodiscard]] constexpr static Vector2 polar_from_cartesian(const double x, const double y)
    {
        return {std::atan2(y, x), std::sqrt(x * x + y * y)};
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

private:
    T x_;
    T y_;
};
