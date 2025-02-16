#include "SumoGame.h"
#include "../Vector2.h"
#include "../NewtonianPhysics.h"
#include "SumoGliders/Glider.h"
#include "SumoGliders/PlayerGlider.h"
#include "SumoGliders/CenteringGlider.h"

#include <chrono>
#include <numbers>
#include <random>
#include <unordered_map>

SumoGame::SumoGame(const std::mt19937& random_generator, Arena arena, const size_t participant_count, const double max_acceleration,
                   const double coefficient_of_friction, const double participant_radius, const double participant_mass,
                   const std::vector<std::shared_ptr<Glider>>& initial_participants) :
    max_acceleration_{max_acceleration},
    coefficient_of_friction_{coefficient_of_friction},
    participant_radius_{participant_radius},
    participant_mass_{participant_mass},
    max_participant_count_{participant_count},
    arena_{std::move(arena)},
    participants_{initial_participants},
    random_generator_{random_generator}
{
    // TODO deal with participants spawning inside each other
    while (participants_.size() < max_participant_count_)
    {
        add_new_participant();
    }
}

const Arena& SumoGame::get_arena() const
{
    return arena_;
}

const std::vector<std::shared_ptr<Glider>>& SumoGame::get_participants() const
{
    return participants_;
}

double SumoGame::get_max_acceleration() const
{
    return max_acceleration_;
}

double SumoGame::get_coefficient_of_friction() const
{
    return coefficient_of_friction_;
}

double SumoGame::get_participant_radius() const
{
    return participant_radius_;
}

double SumoGame::get_participant_mass() const
{
    return participant_mass_;
}

size_t SumoGame::get_max_participant_count() const
{
    return max_participant_count_;
}

void SumoGame::remove_outside_participants(std::vector<std::shared_ptr<Glider>>& participants) const
{
    std::erase_if(participants, [this](const auto& glider)
    {
        return !arena_.contains(glider->get_position());
    });
}

void SumoGame::reset_outside_participants(const std::vector<std::shared_ptr<Glider>>& participants) const
{
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};

    for (const auto& glider : participants)
    {
        if (!arena_.contains(glider->get_position()))
        {
            // Create creature at a uniform, random position within the circular arena
            const auto angle = polar_angle_distribution(random_generator_);
            // This length calculation ensures the distribution is uniform in the arena
            const auto distance_from_center = arena_.get_radius() * std::sqrt(polar_length_distribution(random_generator_));
            const auto position = arena_.get_center() + Vector2<double>::cartesian_from_polar(angle, distance_from_center);
            glider->set_position(position);
        }
    }
}

void SumoGame::add_new_participant()
{
    // Create creature at a uniform, random position within the circular arena
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};

    const auto angle = polar_angle_distribution(random_generator_);
    // This length calculation ensures the distribution is uniform in the arena
    const auto distance_from_center = arena_.get_radius() * std::sqrt(polar_length_distribution(random_generator_));
    const auto position = arena_.get_center() + Vector2<double>::cartesian_from_polar(angle, distance_from_center);

    participants_.emplace_back(std::make_unique<CenteringGlider>(position, participant_mass_, participant_radius_));
}

void SumoGame::update(const std::chrono::high_resolution_clock::time_point& now, const std::chrono::duration<double>& time_step) const
{
    // Ask each creature for their next move (= preferred force)
    // sum up forces for each creature and add friction based on their velocity
    // do physics simulation for each creature, according to the time_step
    // including collision detection and make creatures bounce
    // update positions of creatures using the position of gliders
    // if a creature is outside the arena, remove it

    // TODO detach game loop from rendering loop

    std::unordered_map<std::shared_ptr<Glider>, Vector2<double>> moves;
    for (const auto& glider : participants_)
    {
        const Vector2<double> move_force = glider->next_sumo_move(*this, now, time_step);

        // Assert the move force magnitude is no more than the maximum force magnitude (which is maximum acceleration times mass).
        // Otherwise, next_sumo_move is bugged. No need to check at run time otherwise. Allow for a bit of numerical error
        assert(move_force.get_length() <= glider->get_mass() * max_acceleration_ + 0.0001);

        moves[glider] = move_force;
    }

    NewtonianPhysics<Glider, PhysicsStaticRectangle>::apply_physics(time_step, coefficient_of_friction_, moves, {});

    // Remove participants that are outside the arena
    reset_outside_participants(participants_);

    // Add new participants if there are less than the desired number of participants
    // TODO deal with participants spawning inside each other
    // while (participants_.size() < max_participant_count_)
    // {
    //     add_new_participant();
    // }
}
