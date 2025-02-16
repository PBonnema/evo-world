#include "SumoGame/Arena.h"
#include "SumoGame/SumoGame.h"
#include "SumoGame/SumoGliders/PlayerGlider.h"
#include "SumoGame/SumoGliders/TrajectoryGlider.h"
#include "SumoGame/SumoGliders/CenteringGlider.h"
#include "SumoGame/SumoGliders/RushGlider.h"
#include "RacingGame/RacingTrack.h"
#include "RacingGame/RacingGame.h"
#include "RacingGame/TrackPiece.h"
#include "RacingGame/Racers/PlayerRacer.h"
#include "Vector2_SfVector2f_conversions.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

namespace
{
    void draw_sumo_game(sf::RenderWindow& window, const SumoGame& sumo_game)
    {
        window.clear();

        window.draw(sumo_game.get_arena().get_shape());

        for (const auto& participant : sumo_game.get_participants())
        {
            window.draw(participant->get_shape());
        }

        window.display();
    }

    void draw_racing_game(sf::RenderWindow& window, const RacingGame& racing_game)
    {
        window.clear();

        for (const auto& track_piece : racing_game.get_racing_track().get_track_pieces())
        {
            window.draw(track_piece->get_shape());
        }

        for (const auto& participant : racing_game.get_participants())
        {
            window.draw(participant->get_shape());
        }

        window.display();
    }
}

int main()
{
    // Generate a single seed to be used throughout the application.
    const std::random_device::result_type seed = std::random_device{}();
    std::mt19937 random_generator{seed};

    // Print the seed to the console so that we can reproduce the same results.
    std::cout << "Seed: " << seed << '\n';

    const Vector2 window_dimensions{ 1000u, 1000u};
    sf::RenderWindow window{sf::VideoMode{to_sf_vector2<unsigned int>(window_dimensions)}, "Evo World"};

    // const Arena arena{{500.0, 500.0}, 500.0};
    //
    // constexpr auto mass = 1.0;
    // constexpr auto radius = 80.0;
    // const SumoGame sumo_game{random_generator, arena, 1, 500.0, 100.0, radius, mass,
    //     {
    //         std::make_shared<CenteringGlider>(arena.get_center() + Vector2{ 200.0, 200.0 }, mass, radius),
    //         std::make_shared<RushGlider>(arena.get_center() + Vector2{ -200.0, -200.0 }, mass, radius),
    //         std::make_shared<PlayerGlider>(arena.get_center() + Vector2{ -200.0, -200.0 }, mass, radius, window),
    //         // std::make_shared<TrajectoryGlider>(arena.get_center(), mass, radius,
    //         //     TrajectoryGlider::trajectory_t{
    //         //         {.duration = std::chrono::duration<double>{1.0}, .acceleration = {200.0, 0.0}},
    //         //         {.duration = std::chrono::duration<double>{1.0}, .acceleration = {0.0, 200.0}},
    //         //         {.duration = std::chrono::duration<double>{1.0}, .acceleration = {-200.0, 0.0}},
    //         //         {.duration = std::chrono::duration<double>{1.0}, .acceleration = {0.0, -200.0}},
    //         //     })
    //     }
    // };

    const RacingTrack racing_track{
        {
            std::make_shared<TrackPiece>(Vector2{0.0, 0.0}, Vector2{200.0, 100.0}, 0.0),
        }
    };

    constexpr auto mass = 1.0;
    constexpr auto radius = 80.0;
    const RacingGame racing_game{
        random_generator, racing_track, 500.0, 100.0,
        {
            std::make_shared<PlayerRacer>(Vector2<double>{window_dimensions / 2.0}, mass, radius, window),
        }
    };

    // Game loop
    auto last_time = std::chrono::high_resolution_clock::now();
    while (window.isOpen())
    {
        const auto now = std::chrono::high_resolution_clock::now();
        const auto time_step = now - last_time;

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // sumo_game.update(now, time_step);
        // draw_sumo_game(window, sumo_game);
        racing_game.update(now, time_step);
        draw_racing_game(window, racing_game);

        last_time = now;
    }
}
