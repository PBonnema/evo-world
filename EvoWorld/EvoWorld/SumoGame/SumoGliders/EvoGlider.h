#pragma once
#include "Glider.h"

#include <mdspan>

class EvoGlider final : public Glider
{
public:
    EvoGlider(const Vector2<double>& position, double mass, double radius);

    Vector2<double> next_sumo_move(const SumoGame& sumo_game, const std::chrono::high_resolution_clock::time_point& now,
                                   const std::chrono::duration<double>& time_step) const override;

private:
    // r, x_velocity, y_velocity, angle_opponent, r_opponent, x_velocity_opponent, y_velocity_opponent
    constexpr static size_t number_of_parameters = 7;
    constexpr static size_t number_of_forces_per_parameters = 50;
    const std::array<Vector2<double>, number_of_parameters * number_of_forces_per_parameters> forces_store_;
    // const auto forces_ = std::mdspan{
    //     forces_store_.data(),
    //     number_of_forces_per_parameters, number_of_forces_per_parameters, number_of_forces_per_parameters, number_of_forces_per_parameters,
    //     number_of_forces_per_parameters, number_of_forces_per_parameters, number_of_forces_per_parameters, number_of_forces_per_parameters
    // };
};
