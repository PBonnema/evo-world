#include "Creature.h"
#include "Arena.h"
#include "Vector2.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <numbers>
#include <random>

int main()
{
    std::random_device rd; // Will be used to obtain a seed for the random number engine
    std::mt19937 generator(rd()); // Standard mersenne_twister_engine seeded with rd()

    constexpr double arena_radius = 500.0;
    const Arena arena{arena_radius};
    constexpr Vector2 arena_center{arena_radius, arena_radius};

    std::vector<Creature> creatures;
    creatures.reserve(2);

    std::uniform_real_distribution polar_angle_distribution{0.0, std::numbers::pi * 2};
    std::uniform_real_distribution polar_length_distribution{0.0, 1.0};
    for (size_t i = 0; i < creatures.capacity(); i++)
    {
        // Create creature at a random position within the circular arena
        creatures.emplace_back(arena_center + Creature::position::from_polar(
            polar_angle_distribution(generator), arena_radius * std::sqrt(polar_length_distribution(generator))));
    }

    sf::RenderWindow window(sf::VideoMode({1000, 1000}), "Evo World");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        window.draw(arena.get_shape());

        for (const Creature& creature : creatures)
        {
            window.draw(creature.get_shape());
        }

        window.display();
    }
}
