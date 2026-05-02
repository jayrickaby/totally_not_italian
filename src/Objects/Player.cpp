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
    GRAVITY(900),
    JUMP_STRENGTH(200),
    isGrounded(false),
    direction(0),
    boundingBox({0.f,0.f}, {24.f,24.f}),
    velocity({0,0}){

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

    Animation jump;
    jump.frames.emplace_back(sf::IntRect({96,0}, {24,24}));
    animations.emplace("jump", jump);

    defaultAnimation = "idle";

    sprite.setOrigin(boundingBox.getCenter());
}

void Player::update(float deltaTime) {
    // X DIRECTION
    direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);


    velocity.x = SPEED * direction;
    sprite.setPosition({boundingBox.position.x + (boundingBox.size.x / 2), boundingBox.position.y + (boundingBox.size.y / 2)});

    if (direction != 0) {
        sprite.setScale({direction, 1});
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }

    // Y DIRECTION
    isGrounded = false;
    constexpr float GROUND_LEVEL {0};

    if (boundingBox.position.y >= GROUND_LEVEL) {
        isGrounded = true;
        velocity.y = 0;
        boundingBox.position.y = GROUND_LEVEL;
    }

    const bool INITIATE_JUMP {sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)};

    if (isGrounded && INITIATE_JUMP) {
        velocity.y -= JUMP_STRENGTH;
    }
    else if (!isGrounded) {
        playAnimation("jump");
    }

    velocity.y += GRAVITY * deltaTime;



    // Finalising
    boundingBox.position.x += velocity.x * deltaTime;
    boundingBox.position.y += velocity.y * deltaTime;
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
