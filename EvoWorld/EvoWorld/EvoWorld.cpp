#include "Creature.h"
#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    const std::vector creatures = {
        Creature({0, 0}),
        Creature({300, 500}),
    };

    sf::RenderWindow window(sf::VideoMode({1000, 800}), "Evo World");

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();

        for (const Creature& creature : creatures)
        {
            window.draw(creature.get_shape());
        }

        window.display();
    }
}
