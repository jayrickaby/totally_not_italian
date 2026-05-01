//
// Created by jay on 30/04/2026.
//

#include "Player.h"

#include <algorithm>
#include <iostream>


Player::Player() :
    texture("assets/textures/john/sheet_john_main.png"),
    sprite(texture),
    SPEED(50.f),
    direction(0),
    boundingBox({0.f,0.f}, {24.f,24.f}) {

    Animation idle;
    idle.frames.emplace_back(sf::IntRect({0,0},{24,24}));
    idle.frames.emplace_back(sf::IntRect({24,0},{24,24}));
    idle.frameDuration = 0.5;
    animations.emplace("idle", idle);

    Animation walk;
    walk.frames.emplace_back(sf::IntRect({48,0},{24,24}));
    walk.frames.emplace_back(sf::IntRect({72,0},{24,24}));
    walk.frameDuration = 0.25;
    animations.emplace("walk", walk);

    defaultAnimation = "idle";

    sprite.setOrigin(boundingBox.getCenter());
}

void Player::update(float deltaTime) {
    direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);

    boundingBox.position.x += SPEED * direction * deltaTime;
    sprite.setPosition({boundingBox.position.x + (boundingBox.size.x / 2), boundingBox.position.y + (boundingBox.size.y / 2)});

    if (direction != 0) {
        sprite.setScale({direction, 1});
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }

    animate(deltaTime);
}

void Player::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}

void Player::playAnimation(const std::string& anim) {
    if (defaultAnimation.empty()) {
        defaultAnimation = animations.begin()->first;
    }

    bool validAnim{animations.contains(anim)};

    if (currentAnimation != anim && validAnim) {
        Animation* curAnim {&animations[currentAnimation]};
        curAnim->currentFrame = 0;
        curAnim->frameTimer = 0;

        currentAnimation = anim;
    }
    else if (!validAnim) {
        std::cout << "Animation not found: " << anim << std::endl;
        currentAnimation = defaultAnimation;
    }
}

void Player::animate(float deltaTime) {
    Animation* curAnim {&animations[currentAnimation]};

    curAnim->frameTimer += deltaTime;
    while (curAnim->frameTimer >= curAnim->frameDuration) {
        curAnim->frameTimer -= curAnim->frameDuration;
        curAnim->currentFrame = ++curAnim->currentFrame % curAnim->frames.size();
    }

    sprite.setTextureRect(curAnim->frames[curAnim->currentFrame]);
}
