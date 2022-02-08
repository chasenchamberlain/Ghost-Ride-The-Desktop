#include "cputile.h"

CPUTile::CPUTile(int _row, int _col, int _data, bool _clicked, sf::Sprite _spr)
{
    row = _row;
    col = _col;
    data = _data;
    spr = _spr;
    clicked = _clicked;
    spr.setPosition(300, 300);
}

CPUTile::CPUTile(){}

void CPUTile::SetSpriteInformation(int i, int j)
{
    QResource notClickedSheet(":/images/notClicked.png");
    cpuMockupSheet.loadFromMemory(notClickedSheet.data(), notClickedSheet.size());

    QResource clickedSheet(":/images/clicked.png");
    clickedMockupSheet.loadFromMemory(clickedSheet.data(), clickedSheet.size());
    sf::IntRect rect(0, 0, 186.667, 188.333);

    switch(data)
    {
    case 1:
        rect.left = 0;
        rect.top = 0;
        break;
    case 2:
        rect.left = 186.667;
        rect.top = 0;
        break;
    case 3:
        rect.left = 373.334;
        rect.top = 0;
        break;
    case 4:
        rect.left = 0;
        rect.top = 188.333;
        break;
    case 5:
        rect.left = 186.667;
        rect.top = 188.333;
        break;
    case 6:
        rect.left = 373.334;
        rect.top = 188.333;
        break;
    case 7:
        rect.left = 0;
        rect.top = 376.666;
        break;
    case 8:
        rect.left = 186.667;
        rect.top = 376.666;
        break;
    case 9:
        rect.left = 373.334;
        rect.top = 376.666;
        break;
    }

        if(!clicked)
        {
            sf::Sprite sprite(cpuMockupSheet, rect);
            spr = sprite;
        }
        else
        {
            sf::Sprite sprite(clickedMockupSheet, rect);
            spr = sprite;
        }




   // sprite.scale(2.f, 2.f);
    //spr = sprite;
    spr.setPosition(i, j);
}

bool CPUTile::CheckClicked()
{
    return clicked;
}

void CPUTile::SetClickedFalse()
{
    clicked = false;
}

void CPUTile::SetClickedTrue()
{
    clicked = true;
}

int CPUTile::GetData()
{
    return data;
}
