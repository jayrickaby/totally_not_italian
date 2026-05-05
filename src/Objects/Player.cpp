//
// Created by jay on 30/04/2026.
//

#include "Player.h"
#include "../Types/Animation.h"



Player::Player() :
    SPEED(50.f),
    JUMP_STRENGTH(200),
buf_jump("assets/sounds/jump.mp3"),
tryToJump(false),
snd_jump(buf_jump){

    texture.loadFromFile("assets/textures/john/sheet_john_main.png");

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

void Player::update(float deltaTime) {
    handleInput();
    Entity::update(deltaTime);
}

void Player::handleInput() {
    bool keyAHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A);
    bool keyDHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D);
    bool keySpaceHeld = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    direction = keyDHeld - keyAHeld;

    keySpaceHeld ? tryToJump = true : tryToJump = false;
}

void Player::preMoveY(float deltaTime) {
    if (direction != 0) {
        sprite.setScale({direction, 1});
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }


    if (isGrounded && tryToJump) {
        velocity.y -= JUMP_STRENGTH;
        isGrounded = false;
        tryToJump = false;
        snd_jump.play();
    }
    else if (!isGrounded) {
        playAnimation("jump");
    }
}