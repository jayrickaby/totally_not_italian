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
    boundingBox({0.f,0.f}, {24.f,24.f}) {

    sprite.setOrigin(boundingBox.getCenter());
    sprite.setTextureRect(johnIdleRect);
}

void Player::update(float deltaTime) {
    direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

    boundingBox.position.x += SPEED * direction * deltaTime;
    sprite.setPosition({boundingBox.position.x + (boundingBox.size.x / 2), boundingBox.position.y + (boundingBox.size.y / 2)});

    if (direction != 0) {
        sprite.setScale({direction, 1});
    }
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}
