#ifndef TILE_H
#define TILE_H

#include <QObject>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/AnimatedSprite.hpp"

class Tile
{
protected:
    int row;
    int col;
    int data;
    bool selected;
    sf::Sprite spr;
    AnimatedSprite animatedSprite;
public:
    Tile();
    int GetRow();
    int GetColumn();
    int GetData();
    bool IsSelected();
    sf::Sprite& GetSprite();
    AnimatedSprite GetAnimation();

    void SetRow(int);
    void SetColumn(int);
    void SetData(int);
    void SetSelected(bool);
    void SetSprite(sf::Sprite);
    void SetAnimation(AnimatedSprite);
};

#endif // TILE_H
