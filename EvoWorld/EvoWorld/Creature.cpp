#include "Creature.h"

#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

Creature::Creature(const position& position) :
    position_{position},
    shape_{{std::make_shared<sf::CircleShape>(10.f)}}
{
    sf::CircleShape& circle = *std::static_pointer_cast<sf::CircleShape>(shape_.get_drawables()[0]);
    circle.setFillColor(sf::Color::Red);

    shape_.setPosition({static_cast<float>(position_.get_x()), static_cast<float>(position_.get_y())});
}

const CompoundShape& Creature::get_shape() const
{
    return shape_;
}

CompoundShape& Creature::get_shape()
{
    return shape_;
}
