#include "Creature.h"
#include <SFML/Graphics.hpp>

Creature::Creature(const Position& position)
	: position(position)
{
}

void Creature::draw(sf::RenderTarget& target) const
{
	sf::CircleShape shape(10.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition({ static_cast<float>(position.getX()), static_cast<float>(position.getY()) });
	target.draw(shape);
}
