#pragma once
#include "CompoundShape.h"
#include "Vector2.h"
#include <chrono>

class Glider
{
public:
    Glider(const Vector2<double>& position, double mass, double radius);
    virtual ~Glider() = default;

    [[nodiscard]] const CompoundShape& get_shape() const;
    [[nodiscard]] CompoundShape& get_shape();
    [[nodiscard]] const Vector2<double>& get_position() const;
    [[nodiscard]] const Vector2<double>& get_velocity() const;
    [[nodiscard]] double get_mass() const;
    [[nodiscard]] double get_radius() const;
    void add_position(const Vector2<double>& position);
    void add_velocity(const Vector2<double>& velocity);
    void apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step);
    [[nodiscard]] virtual Vector2<double> next_sumo_move(const std::vector<std::shared_ptr<Glider>>& all_gliders, double max_acceleration,
                                                 double coefficient_of_friction) const;

private:
    CompoundShape shape_; // Class invariant: position of shape_ is equal to position_. It is the center of shape_
    Vector2<double> position_;
    Vector2<double> velocity_;
    double mass_;
    double radius_;
};
