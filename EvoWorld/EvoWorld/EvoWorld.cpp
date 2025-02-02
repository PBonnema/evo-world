#include "Arena.h"
#include "SumoGame.h"
#include "SumoGliders/PlayerGlider.h"
#include "SumoGliders/EvoTrajectoryGlider.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

namespace
{
    void draw_sumo_game(sf::RenderWindow& window, const Arena& arena, const SumoGame& sumo_game)
    {
        window.clear();

        window.draw(arena.get_shape());

        // Draw all creatures from the sumo game
        for (const std::shared_ptr<Glider>& participant : sumo_game.get_participants())
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

    sf::RenderWindow window{sf::VideoMode{{1000, 1000}}, "Evo World"};

    const Arena arena{{500.0, 500.0}, 500.0};

    constexpr auto mass = 1.0;
    constexpr auto radius = 80.0;
    SumoGame sumo_game{random_generator, arena, 1, 500.0, 100.0, radius, mass,
        {
            std::make_shared<PlayerGlider>(arena.get_center(), mass, radius, window),
            std::make_shared<EvoTrajectoryGlider>(arena.get_center(), mass, radius,
                EvoTrajectoryGlider::trajectory_t{
                    {.duration = std::chrono::duration<double>{1.0}, .acceleration = {200.0, 0.0}},
                    {.duration = std::chrono::duration<double>{1.0}, .acceleration = {0.0, 200.0}},
                    {.duration = std::chrono::duration<double>{1.0}, .acceleration = {-200.0, 0.0}},
                    {.duration = std::chrono::duration<double>{1.0}, .acceleration = {0.0, -200.0}},
                })
        }
    };

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

        sumo_game.update(now, time_step);
        draw_sumo_game(window, arena, sumo_game);

        last_time = now;
    }
}
