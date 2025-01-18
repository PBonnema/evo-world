#pragma once
#include <vector>

#include "Arena.h"
#include "fwd_decl.h"

class SumoGame
{
public:
    explicit SumoGame(Arena arena, const std::vector<std::shared_ptr<Creature>>& participants);

    [[nodiscard]] const Arena& get_arena() const;
private:
    const Arena arena_;
    const std::vector<std::shared_ptr<Creature>> participants_;
};
