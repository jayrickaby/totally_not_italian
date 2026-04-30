#include <SFML/Window.hpp>

#include "Objects/Player.h"
#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    Player john;

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event{window.pollEvent()})
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        john.update(deltaTime);

        window.clear();
        john.draw(window);
        window.display();
    }

    return 0;
}
