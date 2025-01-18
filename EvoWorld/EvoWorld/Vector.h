#pragma once
#include <cmath>
#include <algorithm>

template<typename T>
struct Vector
{
public:
	constexpr Vector(T x, T y) : x(x), y(y) {}

	constexpr Vector(const Vector<T>& other) : x(other.x), y(other.y) {}

	constexpr Vector<T> operator+(const Vector<T>& other) const
	{
		return Vector<T>(x + other.x, y + other.y);
	}

	constexpr Vector<T> operator-(const Vector<T>& other) const
	{
		return Vector<T>(x - other.x, y - other.y);
	}

	template<typename U>
	constexpr Vector<T> operator*(U scalar) const
	{
		return Vector<T>(x * scalar, y * scalar);
	}

	template<typename U>
	constexpr Vector<T> operator/(U scalar) const
	{
		return Vector<T>(x / scalar, y / scalar);
	}

	constexpr Vector<T>& operator+=(const Vector<T>& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	constexpr Vector<T>& operator-=(const Vector<T>& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	template<typename U>
	constexpr Vector<T>& operator*=(U scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	template<typename U>
	constexpr Vector<T>& operator/=(U scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	constexpr bool operator==(const Vector<T>& other) const
	{
		return x == other.x && y == other.y;
	}

	constexpr bool operator!=(const Vector<T>& other) const
	{
		return x != other.x || y != other.y;
	}

	constexpr T getX() const
	{
		return x;
	}

	constexpr T getY() const
	{
		return y;
	}

	constexpr void setX(T x)
	{
		this->x = x;
	}

	constexpr void setY(T y)
	{
		this->y = y;
	}

	constexpr void set(T x, T y)
	{
		this->x = x;
		this->y = y;
	}

	template<typename U = T>
	constexpr Vector<U> getNormalized() const
	{
		double length = getLength();
		if (length != 0.0)
			return *this / length;
		else
			return *this;
	}

	constexpr double getLength() const
	{
		return std::sqrt(x * x + y * y);
	}

	constexpr T getLengthSquared() const
	{
		return x * x + y * y;
	}

	constexpr double getAngle() const
	{
		return std::atan2(y, x);
	}

	constexpr double dot(const Vector<T>& other) const
	{
		return x * other.x + y * other.y;
	}

	constexpr Vector<T> getPerpendicular() const
	{
		return Vector<T>(-y, x);
	}

	constexpr Vector<T> getRotated(T angle) const
	{
		T s = std::sin(angle);
		T c = std::cos(angle);
		return Vector<T>(x * c - y * s, x * s + y * c);
	}

	constexpr Vector<T> getReflected(const Vector<T>& normal) const
	{
		return *this - normal * 2 * dot(normal);
	}

	constexpr Vector<T> getProjected(const Vector<T>& axis) const
	{
		return axis * dot(axis) / axis.getLengthSquared();
	}

	constexpr static double distance(const Vector<T>& v1, const Vector<T>& v2)
	{
		return (v1 - v2).getLength();
	}

	constexpr static double distanceSquared(const Vector<T>& v1, const Vector<T>& v2)
	{
		return (v1 - v2).getLengthSquared();
	}

	constexpr static Vector<T> lerp(const Vector<T>& v1, const Vector<T>& v2, T t)
	{
		return v1 + (v2 - v1) * t;
	}

	constexpr static Vector<T> fromPolar(double angle, double length = 1.0)
	{
		return Vector<T>(std::cos(angle) * length, std::sin(angle) * length);
	}

	constexpr static Vector<T> fromPolar(const Vector<T>& v)
	{
		return fromPolar(v.x, v.y);
	}

	constexpr static double angle(const Vector<T>& v1, const Vector<T>& v2)
	{
		return std::atan2(v2.y, v2.x) - std::atan2(v1.y, v1.x);
	}

	constexpr static double angleBetween(const Vector<T>& v1, const Vector<T>& v2)
	{
		return acos(std::clamp(v1.dot(v2), -1.0, 1.0));
	}

	constexpr static double signedAngle(const Vector<T>& v1, const Vector<T>& v2)
	{
		return std::atan2(v2.y, v2.x) - std::atan2(v1.y, v1.x);
	}

	constexpr static double signedAngleBetween(const Vector<T>& v1, const Vector<T>& v2)
	{
		return std::acos(std::clamp(v1.dot(v2), -1.0, 1.0));
	}

	constexpr static double crossProduct(const Vector<T>& v1, const Vector<T>& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	constexpr static Vector<T> min(const Vector<T>& v1, const Vector<T>& v2)
	{
		return Vector<T>(std::min(v1.x, v2.x), std::min(v1.y, v2.y));
	}

	constexpr static Vector<T> max(const Vector<T>& v1, const Vector<T>& v2)
	{
		return Vector<T>(std::max(v1.x, v2.x), std::max(v1.y, v2.y));
	}

	constexpr static Vector<T> floor(const Vector<T>& v)
	{
		return Vector<T>(std::floor(v.x), std::floor(v.y));
	}

	constexpr static Vector<T> ceil(const Vector<T>& v)
	{
		return Vector<T>(std::ceil(v.x), std::ceil(v.y));
	}

	constexpr static Vector<T> round(const Vector<T>& v)
	{
		return Vector<T>(std::round(v.x), std::round(v.y));
	}

	constexpr static Vector<T> abs(const Vector<T>& v)
	{
		return Vector<T>(std::abs(v.x), std::abs(v.y));
	}

	constexpr static Vector<T> clamp(const Vector<T>& v, const Vector<T>& min, const Vector<T>& max)
	{
		return Vector<T>(std::clamp(v.x, min.x, max.x), std::clamp(v.y, min.y, max.y));
	}

	constexpr static Vector<T> clamp(const Vector<T>& v, T min, T max)
	{
		return Vector<T>(std::clamp(v.x, min, max), std::clamp(v.y, min, max));
	}

private:
	T x;
	T y;
};

