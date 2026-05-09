//
// Created by jay on 30/04/2026.
//

#include "Player.h"

#include <iostream>

#include "../Types/Animation.h"



Player::Player() :
    SPEED(50.f),
    JUMP_STRENGTH(200),
tryToJump(false),
buf_jump("assets/sounds/jump.mp3"),
snd_jump(buf_jump){

    setTexture("assets/textures/john/sheet_john_main.png");

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

    // std::string side{""};
    //
    // if (currentlyColliding == CollisionSide::Top) side = "top";
    // else if (currentlyColliding == CollisionSide::Bottom) side = "bottom";
    // else if (currentlyColliding == CollisionSide::Left) side = "left";
    // else if (currentlyColliding == CollisionSide::Right) side = "right";
    // else side = "none";
    //
    // std::cout << side << std::endl;

    Entity::update(deltaTime);
}

void Player::handleInput() {
    const bool keyAHeld {sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)};
    const bool keyDHeld {sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)};
    const bool keySpaceHeld {sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)};

    setDirection(keyDHeld - keyAHeld);

    keySpaceHeld ? tryToJump = true : tryToJump = false;
}

void Player::preMoveY(float deltaTime) {
    if (getDirection() != 0) {
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }

    const bool grounded{isGrounded()};

    if (grounded && tryToJump) {
        velocity.y -= JUMP_STRENGTH;
        setGrounded(false);
        tryToJump = false;
        //snd_jump.play();
    }
    else if (!grounded) {
        playAnimation("jump");
    }
}