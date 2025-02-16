#include "PhysicsStaticRectangle.h"
#include "PhysicsDisk.h"

PhysicsStaticRectangle::PhysicsStaticRectangle(const Vector2<double>& top_left, const Vector2<double>& dimensions,
                                               const double orientation_radians) :
    top_left_{top_left},
    dimensions_{dimensions},
    orientation_radians_{orientation_radians}
{
}

const Vector2<double>& PhysicsStaticRectangle::get_top_left() const
{
    return top_left_;
}

Vector2<double> PhysicsStaticRectangle::get_dimensions() const
{
    return dimensions_;
}

Vector2<double> PhysicsStaticRectangle::get_closest_point(const Vector2<double>& point) const
{
    // Rotate the point around the rectangle's center by the negative orientation
    const auto rotated_point = point.get_rotated_around(top_left_ + dimensions_ / 2, -orientation_radians_);

    // Clamp the point to the rectangle
    const auto clamped_point = rotated_point.get_clamped(top_left_, top_left_ + dimensions_);

    // Rotate the clamped point back
    return clamped_point.get_rotated_around(top_left_ + dimensions_ / 2, orientation_radians_);
}

bool PhysicsStaticRectangle::overlaps(const PhysicsDisk& disk) const
{
    // Rotate the disk's position around the rectangle's center by the negative orientation
    const auto rotated_position = disk.get_position().get_rotated_around(top_left_ + dimensions_ / 2, -orientation_radians_);

    // Check if the disk is inside the rectangle
    const auto rectangle_bottom_right = top_left_ + get_dimensions();
    if (disk.get_position().x() > top_left_.x() + disk.get_radius() &&
        disk.get_position().x() < rectangle_bottom_right.x() - disk.get_radius() &&
        disk.get_position().y() > top_left_.y() + disk.get_radius() &&
        disk.get_position().y() < rectangle_bottom_right.y() - disk.get_radius())
    {
        return true;
    }

    const auto closest_point = get_closest_point(rotated_position);
    return closest_point.distance_squared(rotated_position) < disk.get_radius() * disk.get_radius();
}
