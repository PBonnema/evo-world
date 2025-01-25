#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <ranges>

class CompoundShape final : public sf::Drawable, public sf::Transformable
{
public:
    CompoundShape() = delete;
    explicit CompoundShape(const std::vector<std::unique_ptr<sf::Drawable>>& drawables);
    CompoundShape(const CompoundShape& other) = default;
    CompoundShape(CompoundShape&& other) = default;
    ~CompoundShape() override = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    [[nodiscard]] std::ranges::view auto get_drawables() const
    {
        return drawables_ | std::views::transform([](const auto& drawable) { return drawable.get(); });
    }

private:
    const std::vector<std::unique_ptr<sf::Drawable>> drawables_;
};

