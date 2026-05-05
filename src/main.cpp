#include <SFML/Window.hpp>

#include "Objects/Entity.h"
#include "Objects/Player.h"
#include "SFML/Graphics.hpp"
#include "Types/Animation.h"


int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    Entity goomba;

    Animation goombaIdle;
    goombaIdle.frames.emplace_back(sf::IntRect({0,0}, {16,16}));
    goomba.addAnimation("idle", goombaIdle);

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
        goomba.checkAndCollide(floor.getGlobalBounds());

        window.clear();
        goomba.draw(window);
        window.draw(floor);

        window.display();
    }

    return 0;
}
