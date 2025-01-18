#pragma once
#include "Vector.h"
#include <SFML/Graphics/RenderTarget.hpp>

class Creature
{
public:
	typedef Vector<double> Position;

	Creature(const Position& position);

	void draw(sf::RenderTarget& target) const;

private:
	Position position;
};
