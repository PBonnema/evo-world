#include "Arena.h"

#include <SFML/Graphics/CircleShape.hpp>

Arena::Arena(const Vector2<double>& midpoint, const double radius) :
    midpoint_{midpoint},
    radius_{radius},
    shape_{{std::make_shared<sf::CircleShape>(static_cast<float>(radius), 100)}}
{
    sf::CircleShape& circle = *std::static_pointer_cast<sf::CircleShape>(shape_.get_drawables()[0]);
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
    return Vector2<double>::distance(midpoint_, point) <= radius_;
}
