#pragma once
#include "Vector2.h"

#include <chrono>

class PhysicsDisk
{
public:
    PhysicsDisk(const Vector2<double>& position, double mass, double radius);
    virtual ~PhysicsDisk() = default;

    [[nodiscard]] const Vector2<double>& get_position() const;
    [[nodiscard]] const Vector2<double>& get_velocity() const;
    [[nodiscard]] double get_mass() const;
    [[nodiscard]] double get_radius() const;
    void set_position(const Vector2<double>& position);
    void add_position(const Vector2<double>& displacement);
    void add_velocity(const Vector2<double>& velocity);
    void apply_impulse(const Vector2<double>& force, const std::chrono::duration<double>& time_step);

protected:
    const double mass_;
    const double radius_;

    virtual void on_position_changed(const Vector2<double>& position) = 0;

private:
    Vector2<double> position_;
    Vector2<double> velocity_;
};
