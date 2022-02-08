#include "fantile.h"

FANTile::FANTile(int _x, int _y, int _data, bool _selected, bool _hidden, sf::Sprite _spr, AnimatedSprite _animatedSprite)
{
    row = _x;
    col = _y;
    data = _data;
    selected = _selected;
    hidden = _hidden;
    spr = _spr;
    spr.setPosition(300,300);
    animatedSprite = _animatedSprite;
}

FANTile::FANTile(){}

void FANTile::SetSpriteInformation(int i, int j)
{
    rowcount = i;
    colcount = j;

    QResource questionPNG(":/images/question.png");
    question.loadFromMemory(questionPNG.data(), questionPNG.size());

    QResource sheet(":/images/mockupCoolingSpriteSheet.png");
    fansheet.loadFromMemory(sheet.data(), sheet.size());
    sf::IntRect rect(0, 0, 64, 64);


    switch(data)
    {
    case 1:
        rect.left = 0;
        rect.top = 0;
        break;
    case 2:
        rect.left = 64;
        rect.top = 0;
        break;
    case 3:
        rect.left = 128;
        rect.top = 0;
        break;
    case 4:
        rect.left = 192;
        rect.top = 0;
        break;
    case 5:
        rect.left = 256;
        rect.top = 0;
        break;
    case 6:
        rect.left = 320;
        rect.top = 0;
        break;
    }

    if(hidden)
    {
        sf::Sprite sprite(question);
        spr = sprite;
    }
    else
    {
        sf::Sprite sprite(fansheet, rect);
        spr = sprite;
    }
    spr.setPosition(rowcount, colcount);
}

bool FANTile::CheckHidden()
{
    return hidden;
}

void FANTile::SetHiddenFalse()
{
    hidden = false;
}
