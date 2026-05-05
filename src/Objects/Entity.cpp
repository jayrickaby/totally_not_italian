//
// Created by jay on 05/05/2026.
//

#include "Entity.h"

#include "../Types/Animation.h"

#include <algorithm>
#include <iostream>


Entity::Entity() :
    texture("assets/textures/john/sheet_john_main.png"),
    sprite(texture),
    SPEED(50.f),
    GRAVITY(900),
    isGrounded(false),
    direction(0),
    boundingBox({0.f,0.f}, {24.f,24.f}),
    velocity({0,0}){

    sprite.setOrigin(boundingBox.getCenter());
}

void Entity::update(float deltaTime) {
    // X DIRECTION
    velocity.x = SPEED * direction;
    sprite.setPosition({boundingBox.position.x + (boundingBox.size.x / 2), boundingBox.position.y + (boundingBox.size.y / 2)});

    if (direction != 0) {
        sprite.setScale({direction, 1});
    }

    velocity.y += GRAVITY * deltaTime;

    // Finalising
    boundingBox.position.x += velocity.x * deltaTime;
    boundingBox.position.y += velocity.y * deltaTime;
    animate(deltaTime);
}

void Entity::draw(sf::RenderTarget& target) {
    target.draw(sprite);
}

void Entity::checkAndCollide(const sf::FloatRect& collider) {
    const auto v {boundingBox.findIntersection(collider)};

    if (!v.has_value()) {
        return;
    }

    const sf::FloatRect overlap {v.value()};

    if (overlap.size.x < overlap.size.y) {
        if (velocity.x > 0) {
            boundingBox.position.x -= overlap.size.x;
        }
        else if (velocity.x < 0) {
            boundingBox.position.x += overlap.size.x;
        }

        velocity.x = 0;
    }
    else if (overlap.size.y < overlap.size.x) {
        if (velocity.y > 0){
            boundingBox.position.y -= overlap.size.y;
            isGrounded = true;
        } else if (velocity.y < 0){
            boundingBox.position.y += overlap.size.y;
        }

        velocity.y = 0;
    }
}

void Entity::playAnimation(const std::string& anim) {
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

void Entity::animate(float deltaTime) {
    Animation* curAnim {&animations[currentAnimation]};

    curAnim->frameTimer += deltaTime;
    while (curAnim->frameTimer >= curAnim->frameDuration) {
        curAnim->frameTimer -= curAnim->frameDuration;
        curAnim->currentFrame = ++curAnim->currentFrame % curAnim->frames.size();
    }

    sprite.setTextureRect(curAnim->frames[curAnim->currentFrame]);
}
