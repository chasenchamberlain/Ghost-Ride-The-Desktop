#include "ramtile.h"

RAMTile::RAMTile()
{
}

RAMTile::RAMTile(int _x, int _y, int _data, sf::Sprite _spr, AnimatedSprite _animatedSprite)
{
    row = _x;
    col = _y;
    data = _data;
    selected = false;
    flipped = false;
    matched = false;
    spr = _spr;
    spr.setPosition(300.f, 400.f);
    animatedSprite = _animatedSprite;
}

void RAMTile::SetTexture()
{
    QResource img(":/images/RAMIcons.png");
    original.loadFromMemory(img.data(), img.size());
    QResource matchedrsc(":/images/CoolingSystem.png");
    matchedT.loadFromMemory(matchedrsc.data(), matchedrsc.size());
    QResource flippedrsc(":/images/question.png");
    flippedT.loadFromMemory(flippedrsc.data(), flippedrsc.size());
    sf::IntRect rect(0, 0, 128, 128);

//    if(selected)
//    {
//        //qDebug() << "texture set to selected" << endl;

//        sf::Sprite test(selectedT, rect);
//        spr = test;

//    }
    if(!flipped)
    {
        sf::IntRect rect(0, 0, 64, 64);
        sf::Sprite test(flippedT, rect);
        test.scale(2.f, 2.f);
        spr = test;
    }
    else
    {
        switch(data)
        {
        case 0:
            rect.left = 0;
            rect.top = 0;
            break;
        case 1:
            rect.left = 128;
            rect.top = 0;
            break;
        case 2:
            rect.left = 256;
            rect.top = 0;
            break;
        case 3:
            rect.left = 0;
            rect.top = 128;
            break;
        case 4:
            rect.left = 128;
            rect.top = 128;
            break;
        case 5:
            rect.left = 256;
            rect.top = 128;
            break;
        }
        //qDebug() << "texture set to original" << endl;
        sf::Sprite test(original, rect);
        spr = test;
    }
    spr.setPosition(col * 150 + 10, row * 150 + 10);
}

void RAMTile::Animate()
{

}

bool RAMTile::isMatched()
{
    return matched;
}

bool RAMTile::isFlipped()
{
    return flipped;
}

void RAMTile::Flip()
{
    flipped = !flipped;
    if(!matched)
    {
        Animate();
    }
}

void RAMTile::Match()
{
    matched = true;
}
