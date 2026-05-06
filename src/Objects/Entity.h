//
// Created by jay on 05/05/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_ENTITY_H
#define TOTALLY_NOT_ITALIAN_ENTITY_H
#include "SFML/Graphics.hpp"
#include <map>

struct Animation;
enum class CollisionSide {
    Left,
    Right,
    Top,
    Bottom,
    None
};

class Entity {
public:
    Entity();
    void update(float deltaTime);
    void draw(sf::RenderTarget& target);
    void addAnimation(const std::string& name, const Animation& animation);
    void playAnimation(const std::string& name);

    void checkAndCollide(const sf::FloatRect& collider);
protected:
    // Appearance
    sf::Texture texture;
    sf::Sprite sprite;

    std::map<std::string, Animation> animations;
    std::string currentAnimation;
    std::string defaultAnimation;

    void animate(float deltaTime);

    // Physics
    const float GRAVITY;
    bool isGrounded;
    int direction;
    float speed;
    sf::FloatRect boundingBox;
    sf::Vector2f velocity;
    CollisionSide currentlyColliding;

    void moveX(float deltaTime);
    void moveY(float deltaTime);

    virtual void preMoveX(float deltaTime);
    virtual void preMoveY(float deltaTime);

    virtual void onCollide();
};


#endif //TOTALLY_NOT_ITALIAN_ENTITY_H
