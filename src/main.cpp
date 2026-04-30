#include <SFML/Window.hpp>

#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");
    sf::View camera({0,0}, {256,144});

    window.setView(camera);

    const float JOHN_SPEED {50.f};

    sf::Texture johnTexture("assets/textures/john/sheet_john_main.png");
    sf::Sprite johnSprite{johnTexture};

    sf::IntRect johnIdleRect({0,0},{24,24});
    johnSprite.setTextureRect(johnIdleRect);

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event{window.pollEvent()})
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            johnSprite.setPosition({johnSprite.getPosition().x - JOHN_SPEED * deltaTime, johnSprite.getPosition().y});
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            johnSprite.setPosition({johnSprite.getPosition().x + JOHN_SPEED * deltaTime, johnSprite.getPosition().y});
        }

        window.clear();
        window.draw(johnSprite);
        window.display();
    }

    return 0;
}
