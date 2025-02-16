#pragma once
#include "Vector2.h"

#include <SFML/System/Vector2.hpp>

template<typename Tsf, typename T>
sf::Vector2<Tsf> to_sf_vector2(const Vector2<T>& vector)
{
    return {static_cast<Tsf>(vector.x()), static_cast<Tsf>(vector.y())};
}

template<typename T, typename Tsf>
Vector2<T> to_vector2(const sf::Vector2<Tsf>& vector)
{
    return {static_cast<T>(vector.x), static_cast<T>(vector.y)};
}
