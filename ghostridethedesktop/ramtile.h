#ifndef RAMTILE_H
#define RAMTILE_H

#include <QObject>
#include "tile.h"
#include <SFML/Graphics/Texture.hpp>
#include <QResource>
#include <QDebug>

class RAMTile : public Tile
{
private:
    bool flipped;
    bool matched;
    sf::Texture original;
    sf::Texture matchedT;
    sf::Texture flippedT;
public:
    RAMTile();
    RAMTile(int _x, int _y, int _data, sf::Sprite _spr, AnimatedSprite _animatedSprite);
    void SetTexture();
    void Animate();
    bool isMatched();
    bool isFlipped();
    void Flip();
    void Match();
};

#endif // RAMTILE_H
