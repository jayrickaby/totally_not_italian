//
// Created by jay on 04/05/2026.
//

#include "Goomba.h"

#include "../Types/Animation.h"

Goomba::Goomba() {
    direction = 1;
    texture.loadFromFile("assets/textures/enemies/sheet_goomba.png");

    Animation idle;
    idle.frames.emplace_back(sf::IntRect({0,0}, {16,16}));
    addAnimation("idle", idle);

    Animation walk;
    walk.frames.emplace_back(sf::IntRect({16,0}, {16,16}));
    walk.frames.emplace_back(sf::IntRect({32,0}, {16,16}));
    walk.frameDuration = 0.5f;
    addAnimation("walk", walk);

    speed = 25.f;
}

void Goomba::preMoveX(float deltaTime) {
    if (direction != 0) {
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }
}

void Goomba::onCollide() {
    if (currentlyColliding == CollisionSide::Left) {
        direction = 1;
    }
    else if (currentlyColliding == CollisionSide::Right) {
        direction = -1;
    }
}
