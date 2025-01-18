#pragma once
#include <chrono>
#include <random>
#include <vector>

#include "Arena.h"
#include "fwd_decl.h"

class SumoGame
{
public:
    explicit SumoGame(Arena arena, size_t participant_count, std::random_device::result_type seed);

    [[nodiscard]] const Arena& get_arena() const;
    [[nodiscard]] const std::vector<std::shared_ptr<Creature>>& get_participants() const;
    void update(const std::chrono::duration<double, std::milli>& time_step) const;

private:
    const Arena arena_;
    std::vector<std::shared_ptr<Creature>> participants_;
};
