#ifndef GPUTILE_H
#define GPUTILE_H

#include <QObject>
#include "tile.h"
#include <SFML/Graphics/Texture.hpp>
#include <QResource>
#include <QDebug>

class GPUTile : public Tile
{
    private:
        sf::Texture gpuMockupSheet;
        int rowCount, colCount;
    public:
        int imageIndex;
        void SetSpriteInformation(int i, int j);
        GPUTile();
        GPUTile(int _row, int _col, int _data, bool _selected, sf::Sprite _spr);
};

#endif // GPUTILE_H
