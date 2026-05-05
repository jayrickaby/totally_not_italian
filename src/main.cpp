#include <SFML/Window.hpp>

#include "Objects/Entity.h"
#include "Objects/Goomba.h"
#include "Objects/Player.h"
#include "SFML/Graphics.hpp"
#include "Types/Animation.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    Player john;
    Goomba goomba;

    sf::RectangleShape floor;
    floor.setSize({256,16});
    floor.setPosition({-128,24});


    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event{window.pollEvent()}) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        goomba.update(deltaTime);
        john.update(deltaTime);
        goomba.checkAndCollide(floor.getGlobalBounds());
        john.checkAndCollide(floor.getGlobalBounds());

        window.clear(sf::Color({192,192,255}));
        goomba.draw(window);
        john.draw(window);
        window.draw(floor);

        window.display();
    }

    return 0;
}
