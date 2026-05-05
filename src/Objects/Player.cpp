//
// Created by jay on 30/04/2026.
//

#include "Player.h"
#include "../Types/Animation.h"



Player::Player() :
    SPEED(50.f),
    JUMP_STRENGTH(200),
buf_jump("assets/sounds/jump.mp3"),
snd_jump(buf_jump){

    texture.loadFromFile("assets/textures/john/sheet_john_main.png");
    sprite.setTexture(texture);

    Animation idle;
    idle.frames.emplace_back(sf::IntRect({0,0},{24,24}));
    idle.frames.emplace_back(sf::IntRect({24,0},{24,24}));
    idle.frameDuration = 0.5;
    addAnimation("idle", idle);

    Animation walk;
    walk.frames.emplace_back(sf::IntRect({48,0},{24,24}));
    walk.frames.emplace_back(sf::IntRect({72,0},{24,24}));
    walk.frameDuration = 0.25;
    addAnimation("walk", walk);

    Animation jump;
    jump.frames.emplace_back(sf::IntRect({96,0}, {24,24}));
    addAnimation("jump", jump);

}

void Player::preMoveX(float deltaTime) {
    direction = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) - sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
}

void Player::preMoveY(float deltaTime) {
    if (direction != 0) {
        sprite.setScale({direction, 1});
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }

    const bool INITIATE_JUMP {sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)};

    if (isGrounded && INITIATE_JUMP) {
        velocity.y -= JUMP_STRENGTH;
        isGrounded = false;
        snd_jump.play();
    }
    else if (!isGrounded) {
        playAnimation("jump");
    }
}