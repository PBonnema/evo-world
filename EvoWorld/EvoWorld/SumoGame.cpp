#include "SumoGame.h"

SumoGame::SumoGame(Arena arena, const std::vector<std::shared_ptr<Creature>>& participants) :
    arena_{std::move(arena)},
    participants_{participants}
{
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}
