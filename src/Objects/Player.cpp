//
// Created by jay on 30/04/2026.
//

#include "Player.h"

Player::Player() :
    texture("assets/textures/john/sheet_john_main.png"),
    sprite(texture),
    johnIdleRect({0,0},{24,24}),
    SPEED(50.f),
    direction(0),
    position({0.f,0.f}) {

    sprite.setTextureRect(johnIdleRect);
}

void Player::update(float deltaTime) {
    direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

    position.x += SPEED * direction * deltaTime;
    sprite.setPosition(position);
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}
