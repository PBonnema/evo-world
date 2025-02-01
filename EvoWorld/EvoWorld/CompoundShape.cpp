#include "CompoundShape.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

CompoundShape::CompoundShape(std::vector<std::unique_ptr<sf::Drawable>>&& drawables) :
    drawables_{std::move(drawables)}
{
}

void CompoundShape::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    for (const auto& drawable : drawables_)
    {
        target.draw(*drawable, states);
    }
}
