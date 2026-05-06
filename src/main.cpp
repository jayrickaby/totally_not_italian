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

    std::vector<sf::RectangleShape> collideables;

    sf::RectangleShape floor;
    floor.setSize({256,16});
    floor.setPosition({-128,0});
    collideables.push_back(floor);

    sf::RectangleShape wall1;
    wall1.setSize({16,16});
    wall1.setPosition({-128,-16});
    collideables.push_back(wall1);

    sf::RectangleShape wall2;
    wall2.setSize({16,16});
    wall2.setPosition({112,-16});
    collideables.push_back(wall2);

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

        for (const auto& collideable : collideables) {
            goomba.checkAndCollide(collideable.getGlobalBounds());
            john.checkAndCollide(collideable.getGlobalBounds());
        }

        window.clear(sf::Color({192,192,255}));
        goomba.draw(window);
        john.draw(window);

        for (const auto& collideable : collideables) {
            window.draw(collideable);
        }

        window.display();
    }

    return 0;
}
