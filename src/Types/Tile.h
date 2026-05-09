//
// Created by jay on 09/05/2026.
//

#ifndef TOTALLY_NOT_ITALIAN_TILE_H
#define TOTALLY_NOT_ITALIAN_TILE_H
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

class Tile {
public:
    Tile();
    void draw(sf::RenderTarget &target) const;

    // Getters
    sf::IntRect getBounds() const;

    // Setters
    void setCollideable(bool collideable = true);
    void setPosition(const sf::Vector2i& position);
    void setTexture(const sf::Texture& texture, sf::IntRect rect = {{0,0}, {16,16}});

private:
    sf::Texture texture;
    sf::Sprite sprite;

    sf::IntRect boundingBox;

    bool isCollideable;
};

#endif //TOTALLY_NOT_ITALIAN_TILE_H
