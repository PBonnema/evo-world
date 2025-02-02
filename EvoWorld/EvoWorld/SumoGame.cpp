#include "SumoGame.h"
#include "Vector2.h"
#include "SumoGliders/Glider.h"
#include "SumoGliders/PlayerGlider.h"
#include "SumoGliders/RushGlider.h"
#include "SumoGliders/CenteringGlider.h"

#include <chrono>
#include <numbers>
#include <random>
#include <ranges>
#include <unordered_map>

SumoGame::SumoGame(const std::mt19937& random_generator, Arena arena, const size_t participant_count,
                   const std::vector<std::shared_ptr<Glider>>& initial_participants, const double max_acceleration,
                   const double coefficient_of_friction, const double participant_radius, const double participant_mass) :
    max_acceleration_{max_acceleration},
    coefficient_of_friction_{coefficient_of_friction},
    participant_radius_{participant_radius},
    participant_mass_{participant_mass},
    arena_{std::move(arena)},
    participants_{initial_participants},
    max_participant_count_{participant_count},
    random_generator_{random_generator}
{
    // TODO deal with participants spawning inside each other
    while (participants_.size() < max_participant_count_)
    {
        add_new_participant();
    }

    // participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -450.0), participant_mass_, participant_radius_));
    // participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -200.0 + participant_radius_ * 2), participant_mass_, participant_radius_));
    // participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -200.0 + participant_radius_ * 4), participant_mass_, participant_radius_));
    // participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -200.0 + participant_radius_ * 6), participant_mass_, participant_radius_));
    // participants_.emplace_back(std::make_unique<Glider>(Vector2{0.0, 0.0} + arena_.get_center() + Vector2<double>::from_polar(0.0, -200.0 + participant_radius_ * 8), participant_mass_, participant_radius_));
    // participants_[0]->apply_impulse({100.0, 0.0}, std::chrono::duration<double>{1.0});
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

Vector2<double> SumoGame::calculate_friction(const Glider& glider, const std::chrono::duration<double>& time_step) const
{
    const auto speed = glider.get_velocity().get_length();
    if (speed == 0.0)
    {
        return {0.0, 0.0};
    }

    // The gravitational constant is implicitly set to 1
    auto friction_magnitude = glider.get_mass() * coefficient_of_friction_;

    // Scale the friction such that the impulse does not exceed the remaining momentum of the glider within this time step
    // This prevents the glider from moving backwards. It can come to a full stop.
    const auto friction_impulse = friction_magnitude * time_step.count();
    const auto remaining_momentum = speed * glider.get_mass();
    if (friction_impulse > remaining_momentum)
    {
        friction_magnitude *= remaining_momentum / friction_impulse;
    }

    return glider.get_velocity() / (speed / -friction_magnitude);
}

std::unordered_map<std::shared_ptr<Glider>, std::shared_ptr<Glider>> SumoGame::detect_collisions(
    const std::vector<std::shared_ptr<Glider>>& participants)
{
    std::unordered_map<std::shared_ptr<Glider>, std::shared_ptr<Glider>> collisions;
    // Don't detect collisions between the same glider twice
    for (auto it = participants.begin(); it != participants.end(); ++it)
    {
        for (auto other_it = std::next(it); other_it != participants.end(); ++other_it)
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

void SumoGame::resolve_collision(Glider& glider, Glider& other_glider)
{
    // TODO bug: gliders can now merge when they hug each other with 0 relative velocity (due to friction)
    // TODO Move the gliders apart along the direction of their velocity so they don't overlap. The offset for both should be proportional to their velocity.

    // Bounce as circles
    const auto normal = (other_glider.get_position() - glider.get_position()).get_normalized();
    const auto relative_velocity = other_glider.get_velocity() - glider.get_velocity();
    const auto velocity_along_normal = relative_velocity.dot(normal);

    if (velocity_along_normal <= 0.0)
    {
        constexpr auto e = 1.0; // Perfectly elastic collision
        const auto impulse_magnitude = -(1.0 + e) * velocity_along_normal / (1.0 / glider.get_mass() + 1.0 / other_glider.get_mass());

        const auto impulse = normal * impulse_magnitude;
        glider.add_velocity(-impulse / glider.get_mass());
        other_glider.add_velocity(impulse / other_glider.get_mass());
    }
}

void SumoGame::remove_outside_participants(std::vector<std::shared_ptr<Glider>>& participants) const
{
    std::erase_if(participants, [this](const auto& glider)
    {
        return !arena_.contains(glider->get_position());
    });
}

void SumoGame::add_new_participant()
{
    // Create creature at a uniform, random position within the circular arena
    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};

    const auto angle = polar_angle_distribution(random_generator_);
    // This length calculation ensures the distribution is uniform in the arena
    const auto distance_from_center = arena_.get_radius() * std::sqrt(polar_length_distribution(random_generator_));
    const auto position = arena_.get_center() + Vector2<double>::from_polar(angle, distance_from_center);

    participants_.emplace_back(std::make_unique<CenteringGlider>(position, participant_mass_, participant_radius_));
}

void SumoGame::update(const std::chrono::duration<double>& time_step)
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
        const Vector2<double> move_force = glider->next_sumo_move(*this);

        // Assert the move force magnitude is no more than the maximum force magnitude (which is maximum acceleration times mass).
        // Otherwise, next_sumo_move is bugged. No need to check at run time otherwise. Allow for a bit of numerical error
        assert(move_force.get_length() <= glider->get_mass() * max_acceleration_ + 0.0001);

        moves[glider] = move_force;
    }

    for (const auto& [glider, move_force] : moves)
    {
        const auto friction = calculate_friction(*glider, time_step);

        // Sum up all forces and apply them
        const auto total_force = move_force + friction;
        glider->apply_impulse(total_force, time_step);
    }

    // Collision handling
    for (const auto& [glider, other_glider] : detect_collisions(participants_))
    {
        resolve_collision(*glider, *other_glider);
        // TODO perfect this by playing time up until the first collision, resolve it, and continue time until the next collision, recursively
    }

    // Remove participants that are outside the arena
    remove_outside_participants(participants_);

    // Add new participants if there are less than the desired number of participants
    // TODO deal with participants spawning inside each other
    while (participants_.size() < max_participant_count_)
    {
        add_new_participant();
    }
}
