#include <SFML/Window.hpp>

#include "Objects/Player.h"
#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    Player john;

    sf::Texture bedroomSheet("assets/textures/area/sheet_bedroom.png");
    sf::IntRect floorRect({0,0}, {16,16});

    std::vector<sf::Sprite> floor;
    for (int i = 0; i < 16; i++) {
        sf::Sprite spr(bedroomSheet);
        spr.setTextureRect(floorRect);
        spr.setPosition({-128.f + (16.f*i), 24.f});

        floor.emplace_back(spr);
    }

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event{window.pollEvent()}) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        john.update(deltaTime);

        window.clear();
        john.draw(window);
        for (const auto& tile : floor ) {
            window.draw(tile);
        }

        window.display();
    }

    return 0;
}
