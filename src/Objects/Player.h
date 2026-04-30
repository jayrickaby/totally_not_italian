//
// Created by jay on 30/04/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_PLAYER_H
#define TOTALLY_NOT_ITALIAN_PLAYER_H
#include "SFML/Graphics.hpp"


class Player {
public:
    Player();
    void update(float deltaTime);
    void draw(sf::RenderTarget& target);

private:
    // Appearance
    sf::Texture texture;
    sf::Sprite sprite;

    sf::IntRect johnIdleRect;


    // Physics
    const float SPEED;

    int direction;
    sf::Vector2f position;
};


#endif //TOTALLY_NOT_ITALIAN_PLAYER_H
