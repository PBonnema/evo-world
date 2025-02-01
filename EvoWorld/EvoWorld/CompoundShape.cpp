#include "CompoundShape.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

CompoundShape::CompoundShape(const std::vector<std::shared_ptr<sf::Drawable>>& drawables) :
    drawables_{drawables}
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

const std::vector<std::shared_ptr<sf::Drawable>>& CompoundShape::get_drawables() const
{
    return drawables_;
}
