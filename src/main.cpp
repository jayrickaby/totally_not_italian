#include <SFML/Window.hpp>

#include "SFML/Graphics.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode({1280, 720}), "Totally Not Italian");

    while (window.isOpen()) {
        while (const std::optional event{window.pollEvent()})
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        window.clear();
        window.display();
    }

    return 0;
}
