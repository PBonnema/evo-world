#pragma once
#include "fwd_decl.h"

#include <chrono>
#include <random>
#include <unordered_map>

class NewtonianDiskPhysics
{
public:
    void update(const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step,
                   const double coefficient_of_friction, const std::vector<std::shared_ptr<PhysicsDisk>>& disks,
                   const std::unordered_map<std::shared_ptr<PhysicsDisk>, Vector2<double>>& forces);

private:
    [[nodiscard]] Vector2<double> calculate_friction(const PhysicsDisk& disk, const std::chrono::duration<double>& time_step) const;
    [[nodiscard]] static std::unordered_map<std::shared_ptr<PhysicsDisk>, std::shared_ptr<PhysicsDisk>> detect_collisions(
        const std::vector<std::shared_ptr<PhysicsDisk>>& disks);
    static void resolve_collision(PhysicsDisk& disk, PhysicsDisk& other_disk);
};
