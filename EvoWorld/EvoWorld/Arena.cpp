#include "Arena.h"

#include <SFML/Graphics/CircleShape.hpp>

Arena::Arena(const double radius) :
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

double Arena::get_radius() const
{
    return radius_;
}
