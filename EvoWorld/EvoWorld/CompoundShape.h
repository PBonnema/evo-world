#pragma once
#include <memory>
#include <span>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>

class CompoundShape final : public sf::Drawable, public sf::Transformable
{
public:
    CompoundShape() = default;
    CompoundShape(const std::vector<std::shared_ptr<sf::Drawable>>& drawables);
    CompoundShape(std::initializer_list<std::shared_ptr<sf::Drawable>> drawables);
    CompoundShape(const CompoundShape& other) = default;
    CompoundShape(CompoundShape&& other) = default;
    ~CompoundShape() override = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    [[nodiscard]] std::span<const std::shared_ptr<sf::Drawable>> get_drawables() const;

private:
    const std::vector<std::shared_ptr<sf::Drawable>> drawables_;
};
