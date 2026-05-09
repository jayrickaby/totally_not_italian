#include <ranges>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <map>
#include <utility>
#include "Objects/Entity.h"
#include "Objects/Goomba.h"
#include "Objects/Player.h"
#include "Types/Tile.h"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    Player john;
    Goomba goomba;

    sf::Texture groundTexture("assets/textures/area/sheet_mario.png");

    Tile groundTile;
    groundTile.setCollideable();
    groundTile.setTexture(groundTexture);

    std::map<std::pair<int, int>, Tile> level;

    for (int x = 0; x < 16; x++) {
        groundTile.setPosition({x*16 - 128,0});
        level[{x*16, 0}] = groundTile;
    }

    groundTile.setPosition({-64,-16});
    level[{-64,-16}] = groundTile;

    groundTile.setPosition({64,-16});
    level[{64,-16}] = groundTile;

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

        for (const auto &tile: level | std::views::values) {
            goomba.checkAndCollide(sf::FloatRect(tile.getBounds()));
            john.checkAndCollide(sf::FloatRect(tile.getBounds()));
        }

        window.clear(sf::Color({192,192,255}));
        goomba.draw(window);
        john.draw(window);

        for (const auto &tile: level | std::views::values) {
            tile.draw(window);
        }

        window.display();
    }

    return 0;
}
