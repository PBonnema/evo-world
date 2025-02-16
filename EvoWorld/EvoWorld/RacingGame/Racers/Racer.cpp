#include "Racer.h"

#include <SFML/Graphics/CircleShape.hpp>

Racer::Racer(const Vector2<double>& position, const double mass, const double radius) :
    PhysicsDisk{position, mass, radius},
    shape_{{std::make_shared<sf::CircleShape>(static_cast<float>(radius))}}
{
    shape_.setOrigin(sf::Vector2f{static_cast<float>(radius), static_cast<float>(radius)});
    shape_.setPosition({static_cast<float>(get_position().x()), static_cast<float>(get_position().y())});
}

const CompoundShape& Racer::get_shape() const
{
    return shape_;
}

CompoundShape& Racer::get_shape()
{
    return shape_;
}

void Racer::on_position_changed(const Vector2<double>& position)
{
    shape_.setPosition({static_cast<float>(position.x()), static_cast<float>(position.y())});
}
