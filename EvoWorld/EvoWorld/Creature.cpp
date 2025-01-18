#include "Creature.h"

#include <memory>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>

Creature::Creature(const position& position) :
    position_{position},
    shape_{{std::make_shared<sf::CircleShape>(10.f), std::make_shared<sf::CircleShape>(10.f)}}
{
    sf::CircleShape& circle1 = *std::static_pointer_cast<sf::CircleShape>(shape_.get_drawables()[0]);
    circle1.setFillColor(sf::Color::Green);

    sf::CircleShape& circle2 = *std::static_pointer_cast<sf::CircleShape>(shape_.get_drawables()[1]);
    circle2.setFillColor(sf::Color::Red);
    circle2.setPosition({20.f, 0.f});

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
