#include "Arena.h"

#include <SFML/Graphics/CircleShape.hpp>

Arena::Arena(const Vector2<double>& center, const double radius) :
    center_{center},
    radius_{radius},
    shape_{{std::make_unique<sf::CircleShape>(static_cast<float>(radius), 100)}}
{
    auto& circle = *dynamic_cast<sf::CircleShape*>(shape_.get_drawables()[0].get());
    circle.setFillColor(sf::Color::Blue);
}

const CompoundShape& Arena::get_shape() const
{
    return shape_;
}

CompoundShape& Arena::get_shape()
{
    return shape_;
}

bool Arena::contains(const Vector2<double>& point) const
{
    return center_.distance(point) <= radius_;
}
