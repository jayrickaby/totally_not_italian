//
// Created by jay on 09/05/2026.
//

#include "Tile.h"

#include "../Managers/AssetManager.h"
#include "SFML/Graphics.hpp"

Tile::Tile() :
sprite(*AssetManager::getTexture("dev/missing.png")),
boundingBox({0,0}, {16,16}),
isCollideable(false) {
    setPosition({0,0});
}

void Tile::draw(sf::RenderTarget &target) const {
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
    //
    // target.draw(bounds);
    target.draw(sprite);
    // target.draw(origin);
}

sf::IntRect Tile::getBounds() const {
    return boundingBox;
}

void Tile::setCollideable(bool collideable) {
    isCollideable = collideable;
}

void Tile::setPosition(const sf::Vector2i &position) {
    boundingBox.position = position;

    sf::Vector2f size{boundingBox.size};
    sf::Vector2f center{boundingBox.getCenter()};

    sprite.setOrigin({(size.x / 2), (size.y / 2)});
    sprite.setPosition(center);
}

void Tile::setTexture(const sf::Texture* texture, const sf::IntRect& rect) {
    sprite.setTexture(*texture);
    sprite.setTextureRect(rect);
}
