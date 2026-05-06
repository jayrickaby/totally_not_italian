//
// Created by jay on 04/05/2026.
//

#include "Goomba.h"

#include "../Types/Animation.h"

Goomba::Goomba() {
    setDirection(1);
    setSpeed(25.f);
    setTexture("assets/textures/enemies/sheet_goomba.png");

    Animation idle;
    idle.frames.emplace_back(sf::IntRect({0,0}, {16,16}));
    addAnimation("idle", idle);

    Animation walk;
    walk.frames.emplace_back(sf::IntRect({16,0}, {16,16}));
    walk.frames.emplace_back(sf::IntRect({32,0}, {16,16}));
    walk.frameDuration = 0.5f;
    addAnimation("walk", walk);
}

void Goomba::preMoveX(float deltaTime) {
    if (getDirection() != 0) {
        playAnimation("walk");
    }
    else {
        playAnimation("idle");
    }
}

void Goomba::onCollide() {
    const CollisionSide currentlyColliding{getCurrentColliding()};

    if (currentlyColliding == CollisionSide::Left) {
         setDirection(1);
    }
    else if (currentlyColliding == CollisionSide::Right) {
        setDirection(-1);
    }
}
