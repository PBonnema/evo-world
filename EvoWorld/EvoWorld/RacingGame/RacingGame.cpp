#include "RacingGame.h"
#include "../NewtonianPhysics.h"
#include "Racers/Racer.h"

#include <chrono>
#include <random>

RacingGame::RacingGame(const std::mt19937& random_generator, RacingTrack racing_track, const double max_acceleration,
                   const double coefficient_of_friction, const std::vector<std::shared_ptr<Racer>>& participants) :
    max_acceleration_{max_acceleration},
    coefficient_of_friction_{coefficient_of_friction},
    racing_track_{std::move(racing_track)},
    participants_{participants},
    random_generator_{random_generator}
{
}

const RacingTrack& RacingGame::get_racing_track() const
{
    return racing_track_;
}

const std::vector<std::shared_ptr<Racer>>& RacingGame::get_participants() const
{
    return participants_;
}

double RacingGame::get_max_acceleration() const
{
    return max_acceleration_;
}

double RacingGame::get_coefficient_of_friction() const
{
    return coefficient_of_friction_;
}

void RacingGame::update(const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    // Ask each creature for their next move (= preferred force)
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders
    // if a creature is outside the arena, remove it

    const std::unordered_map<std::shared_ptr<Racer>, Vector2<double>> moves{
        {participants_[0], participants_[0]->next_move(*this, now, time_step)}
    };
    NewtonianPhysics<Racer, TrackPiece>::apply_physics(time_step, coefficient_of_friction_, moves, racing_track_.get_track_pieces());
}
