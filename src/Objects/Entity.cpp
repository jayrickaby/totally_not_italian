//
// Created by jay on 05/05/2026.
//

#include "Entity.h"

#include "../Types/Animation.h"

#include <algorithm>
#include <iostream>


Entity::Entity() :
    texture("assets/textures/dev/missing.png"),
    sprite(texture),
    SPEED(50.f),
    GRAVITY(900),
    isGrounded(false),
    direction(0),
    boundingBox({0.f,0.f}, sprite.getLocalBounds().size),
    velocity({0,0}){}

void Entity::update(float deltaTime) {
    moveX(deltaTime);
    moveY(deltaTime);

    animate(deltaTime);
}

void Entity::preMoveX(float deltaTime) {

}

void Entity::preMoveY(float deltaTime) {

}

void Entity::moveX(float deltaTime) {
    preMoveX(deltaTime);
    velocity.x = SPEED * direction;
    boundingBox.position.x += velocity.x * deltaTime;
}

void Entity::moveY(float deltaTime) {
    preMoveY(deltaTime);
    velocity.y += GRAVITY * deltaTime;
    boundingBox.position.y += velocity.y * deltaTime;
}

void Entity::draw(sf::RenderTarget& target) {
    // sf::RectangleShape bbRect;
    // bbRect.setSize(boundingBox.size);
    // bbRect.setPosition(boundingBox.position);
    // bbRect.setFillColor(sf::Color::Blue);
    // target.draw(bbRect);

    target.draw(sprite);

    // sf::CircleShape originCirc;
    // originCirc.setRadius(2);
    // originCirc.setPosition({sprite.getPosition().x + sprite.getOrigin().x, sprite.getPosition().y + sprite.getOrigin().y});
    // originCirc.setFillColor(sf::Color::Red);
    // target.draw(originCirc);
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
