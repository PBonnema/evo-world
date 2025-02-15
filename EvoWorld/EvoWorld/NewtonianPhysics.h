#pragma once
#include "Vector2.h"
#include "fwd_decl.h"

#include <chrono>
#include <random>
#include <unordered_map>

template <typename TDisk> requires std::derived_from<TDisk, PhysicsDisk>
class NewtonianPhysics
{
public:
    static void apply_physics(const std::chrono::duration<double>& time_step, double coefficient_of_friction,
                              const std::vector<std::shared_ptr<TDisk>>& disks,
                              const std::unordered_map<std::shared_ptr<TDisk>, Vector2<double>>& forces);

private:
    [[nodiscard]] static Vector2<double> calculate_friction(const TDisk& disk, const std::chrono::duration<double>& time_step,
                                                            double coefficient_of_friction);
    [[nodiscard]] static std::unordered_map<std::shared_ptr<TDisk>, std::shared_ptr<TDisk>> detect_collisions(
        const std::vector<std::shared_ptr<TDisk>>& disks);
    static void resolve_collision(TDisk& disk, TDisk& other_disk);
};

template <typename TDisk> requires std::derived_from<TDisk, PhysicsDisk>
void NewtonianPhysics<TDisk>::apply_physics(const std::chrono::duration<double>& time_step, const double coefficient_of_friction,
                                            const std::vector<std::shared_ptr<TDisk>>& disks,
                                            const std::unordered_map<std::shared_ptr<TDisk>, Vector2<double>>& forces)
{
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders

    for (const auto& [disk, move_force] : forces)
    {
        const auto friction = calculate_friction(*disk, time_step, coefficient_of_friction);

        // Sum up all forces and apply them
        const auto total_force = move_force + friction;
        disk->apply_impulse(total_force, time_step);
    }

    // Collision handling
    for (const auto& [glider, other_glider] : detect_collisions(disks))
    {
        resolve_collision(*glider, *other_glider);
        // TODO perfect this by playing time up until the first collision, resolve it, and continue time until the next collision, recursively
    }
}

template <typename TDisk> requires std::derived_from<TDisk, PhysicsDisk>
Vector2<double> NewtonianPhysics<TDisk>::calculate_friction(const TDisk& disk, const std::chrono::duration<double>& time_step,
                                                            double coefficient_of_friction)
{
    const auto speed = disk.get_velocity().get_length();
    if (speed == 0.0)
    {
        return {0.0, 0.0};
    }

    // The gravitational constant is implicitly set to 1
    auto friction_magnitude = disk.get_mass() * coefficient_of_friction;

    // Scale the friction such that the impulse does not exceed the remaining momentum of the glider within this time step
    // This prevents the glider from moving backwards. It can come to a full stop.
    const auto friction_impulse = friction_magnitude * time_step.count();
    const auto remaining_momentum = speed * disk.get_mass();
    if (friction_impulse > remaining_momentum)
    {
        friction_magnitude *= remaining_momentum / friction_impulse;
    }

    return disk.get_velocity() / (speed / -friction_magnitude);
}

template <typename TDisk> requires std::derived_from<TDisk, PhysicsDisk>
std::unordered_map<std::shared_ptr<TDisk>, std::shared_ptr<TDisk>> NewtonianPhysics<TDisk>::detect_collisions(
    const std::vector<std::shared_ptr<TDisk>>& disks)
{
    std::unordered_map<std::shared_ptr<TDisk>, std::shared_ptr<TDisk>> collisions;
    // Don't detect collisions between the same glider twice
    for (auto it = disks.cbegin(); it != disks.cend(); ++it)
    {
        for (auto other_it = std::next(it); other_it != disks.cend(); ++other_it)
        {
            const auto distance_squared = (*it)->get_position().distance_squared((*other_it)->get_position());
            const auto radius_sum = (*it)->get_radius() + (*other_it)->get_radius();
            if (distance_squared < radius_sum * radius_sum)
            {
                collisions[*it] = *other_it;
            }
        }
    }

    return collisions;
}

template <typename TDisk> requires std::derived_from<TDisk, PhysicsDisk>
void NewtonianPhysics<TDisk>::resolve_collision(TDisk& disk, TDisk& other_disk)
{
    // TODO bug: gliders can now merge when they hug each other with 0 relative velocity (due to friction)
    // TODO Move the gliders apart along the direction of their velocity so they don't overlap. The offset for both should be proportional to their velocity.

    // Bounce as circles
    const auto normal = (other_disk.get_position() - disk.get_position()).get_normalized();
    const auto relative_velocity = other_disk.get_velocity() - disk.get_velocity();
    const auto velocity_along_normal = relative_velocity.dot(normal);

    if (velocity_along_normal <= 0.0)
    {
        constexpr auto e = 1.0; // Perfectly elastic collision
        const auto impulse_magnitude = -(1.0 + e) * velocity_along_normal / (1.0 / disk.get_mass() + 1.0 / other_disk.get_mass());

        const auto impulse = normal * impulse_magnitude;
        disk.add_velocity(-impulse / disk.get_mass());
        other_disk.add_velocity(impulse / other_disk.get_mass());
    }
}
