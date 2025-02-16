#include "TrackPiece.h"
#include "../Vector2.h"
#include "../Vector2_SfVector2f_conversions.h"

#include <SFML/Graphics/RectangleShape.hpp>

TrackPiece::TrackPiece(const Vector2<double>& top_left, const Vector2<double>& dimensions, const double orientation_radians) :
    PhysicsStaticRectangle{top_left, dimensions, orientation_radians},
    shape_{{std::make_shared<sf::RectangleShape>(to_sf_vector2<float>(dimensions))}}
{
    auto& shape = *dynamic_cast<sf::RectangleShape*>(shape_.get_drawables()[0].get());
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(to_sf_vector2<float>(top_left));
    shape.setRotation(sf::radians(static_cast<float>(orientation_radians)));
}

const CompoundShape& TrackPiece::get_shape() const
{
    return shape_;
}
