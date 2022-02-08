#ifndef CPUTILE_H
#define CPUTILE_H

#include <QObject>
#include "tile.h"
#include <SFML/Graphics/Texture.hpp>
#include <QResource>
#include <QDebug>

class CPUTile : public Tile
{
    private:
        bool clicked;
        sf::Texture cpuMockupSheet;
        sf::Texture clickedMockupSheet;
        int rowCount, colCount;
    public:
        void SetSpriteInformation(int i, int j);
        CPUTile();
        CPUTile(int _row, int _col, int data, bool _clicked, sf::Sprite _spr);
        bool CheckClicked();
        void SetClickedFalse();
        void SetClickedTrue();
        int GetData();
};

#endif // CPUTILE_H
