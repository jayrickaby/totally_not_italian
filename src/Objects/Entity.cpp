//
// Created by jay on 05/05/2026.
//

#include "Entity.h"

#include "../Managers/AssetManager.h"
#include "../Types/Animation.h"

#include <algorithm>
#include <iostream>


Entity::Entity() :
    grounded(false),
    direction(0),
    boundingBox({0.f,0.f}, sprite.getLocalBounds().size),
    velocity({0,0}),
    sprite(*AssetManager::getTexture("dev/missing.png")),
    GRAVITY(900),
    speed(50.f){}

void Entity::update(float deltaTime) {
    moveX(deltaTime);
    moveY(deltaTime);

    currentlyColliding = CollisionSide::None;

    animate(deltaTime);
}

void Entity::preMoveX(float deltaTime) {

}

void Entity::preMoveY(float deltaTime) {

}

void Entity::moveX(float deltaTime) {
    preMoveX(deltaTime);
    velocity.x = speed * direction;
    boundingBox.position.x += velocity.x * deltaTime;
}

void Entity::moveY(float deltaTime) {
    preMoveY(deltaTime);
    velocity.y += GRAVITY * deltaTime;
    boundingBox.position.y += velocity.y * deltaTime;
}

void Entity::draw(sf::RenderTarget& target) {
    // sf::RectangleShape bounds;
    // bounds.setPosition(sf::Vector2f(boundingBox.position));
    // bounds.setSize(sf::Vector2f(boundingBox.size));
    // bounds.setFillColor(sf::Color::Blue);
    //
    // sf::CircleShape origin;
    // origin.setOrigin(sprite.getOrigin());
    // origin.setPosition(sprite.getPosition() + sprite.getOrigin());
    // origin.setRadius(1);
    // origin.setFillColor(sf::Color::Red);

    // target.draw(bounds);
    target.draw(sprite);
    // target.draw(origin);
}

void Entity::addAnimation(const std::string& name, const Animation& animation) {
    if (animation.frames.empty()) {
        std::cout << "Can't add empty \'" << name << "\' animation!" << std::endl;
        return;
    }

    if (animations.empty()) {
        defaultAnimation = name;
    }

    animations.emplace(name, animation);
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
            currentlyColliding = CollisionSide::Right;
        }
        else if (velocity.x < 0) {
            boundingBox.position.x += overlap.size.x;
            currentlyColliding = CollisionSide::Left;
        }

        velocity.x = 0;
    }
    else if (overlap.size.y < overlap.size.x) {
        if (velocity.y > 0){
            boundingBox.position.y -= overlap.size.y;
            grounded = true;
            currentlyColliding = CollisionSide::Bottom;
        } else if (velocity.y < 0){
            boundingBox.position.y += overlap.size.y;
            currentlyColliding = CollisionSide::Top;
        }

        velocity.y = 0;
    }

    onCollide();
}

void Entity::playAnimation(const std::string& name) {
    if (animations.empty()) {
        std::cout << "No animations!" << std::endl;
        return;
    }

    if (defaultAnimation.empty()) {
        defaultAnimation = animations.begin()->first;
    }

    bool validAnim{animations.contains(name)};

    if (currentAnimation != name && validAnim) {
        Animation* curAnim {&animations[currentAnimation]};
        curAnim->currentFrame = 0;
        curAnim->frameTimer = 0;

        currentAnimation = name;
    }
    else if (!validAnim) {
        std::cout << "Animation not found: " << name << std::endl;
        currentAnimation = defaultAnimation;
    }
}

void Entity::animate(float deltaTime) {
    if (direction != 0) {
        sprite.setScale({direction, 1});
    }

    if (currentAnimation.empty()) {
        currentAnimation = defaultAnimation;
    }

    Animation* curAnim {&animations[currentAnimation]};

    curAnim->frameTimer += deltaTime;
    while (curAnim->frameTimer >= curAnim->frameDuration) {
        curAnim->frameTimer -= curAnim->frameDuration;
        curAnim->currentFrame = ++curAnim->currentFrame % curAnim->frames.size();
    }

    sprite.setTextureRect(curAnim->frames[curAnim->currentFrame]);

    // @TODO When adding proper animation support, bounding box is baked into each frame allowing for custom sizes.
    // Make sure bounding box accurate to sprite
    boundingBox.size = sf::Vector2f(sprite.getTextureRect().size);

    // Make sure sprite flips correctly when turning
    sprite.setOrigin({(boundingBox.size.x/2), (boundingBox.size.y/2)});
    sprite.setPosition(boundingBox.getCenter());
}

void Entity::onCollide() {

}

void Entity::setSpeed(float newSpeed) {
    speed = newSpeed;
}

void Entity::setTexture(const sf::Texture* texture) {
    sprite.setTexture(*texture);
}

void Entity::setDirection(int newDirection) {
    direction = newDirection;
}

int Entity::getDirection() const {
    return direction;
}

CollisionSide Entity::getCurrentColliding() const {
    return currentlyColliding;
}

bool Entity::isGrounded() const {
    return grounded;
}

void Entity::setGrounded(bool state) {
    grounded = state;
}
