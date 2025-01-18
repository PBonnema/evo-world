#include "Creature.h"
#include "Arena.h"
#include "SumoGame.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>

int main()
{
    const std::random_device::result_type seed = std::random_device{}(); // Will be used to obtain a seed for the random number engine
    std::cout << "Seed: " << seed << '\n';

    const Arena arena{500.0};
    const SumoGame sumo_game{arena, 2, seed};
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

        for (const std::shared_ptr<Creature>& creature : sumo_game.get_participants())
        {
            window.draw(creature->get_shape());
        }

        window.display();
    }
}
