#ifndef FANTILE_H
#define FANTILE_H

#include <QObject>
#include "tile.h"
#include <SFML/Graphics/Texture.hpp>
#include <QResource>
#include <QDebug>

class FANTile : public Tile
{
private:
    bool hidden;
    void setSpritePosition();
    sf::Texture fansheet;
    sf::Texture question;
    int rowcount, colcount;
    bool loopstart;
public:
    FANTile();
    FANTile(int _x, int _y, int _data, bool _selected, bool _hidden, sf::Sprite _spr, AnimatedSprite _animatedSprite);
    bool CheckHidden();
    void SetSpriteInformation(int i, int j);

    void SetHiddenFalse();


};

#endif // FANTILE_H
