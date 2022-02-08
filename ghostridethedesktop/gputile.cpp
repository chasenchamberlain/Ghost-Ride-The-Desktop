#include "gputile.h"

GPUTile::GPUTile(int _row, int _col, int _imageIndex, bool _selected, sf::Sprite _spr)
{
    row = _row;
    col = _col;
    imageIndex = _imageIndex;
    selected = _selected;
    spr = _spr;
    spr.setPosition(300, 300);
}

GPUTile::GPUTile(){}

void GPUTile::SetSpriteInformation(int i, int j)
{
    QResource sheet(":/images/RedBaronTiles.png");
    gpuMockupSheet.loadFromMemory(sheet.data(), sheet.size());
    sf::IntRect rect(0, 0, 150, 150);

    switch(imageIndex)
    {
    case 1:
        rect.left = 0;
        rect.top = 0;
        break;
    case 2:
        rect.left = 150;
        rect.top = 0;
        break;
    case 3:
        rect.left = 300;
        rect.top = 0;
        break;
    case 4:
        rect.left = 450;
        rect.top = 0;
        break;
    case 5:
        rect.left = 600;
        rect.top = 0;
        break;
    case 6:
        rect.left = 750;
        rect.top = 0;
        break;
    case 7:
        rect.left = 900;
        rect.top = 0;
        break;
    case 8:
        rect.left = 1050;
        rect.top = 0;
        break;
    case 9:
        rect.left = 1200;
        rect.top = 0;
        break;
    }

    sf::Sprite sprite(gpuMockupSheet, rect);
    spr = sprite;
    spr.setPosition(i, j);
}


