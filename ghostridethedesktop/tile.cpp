#include "tile.h"

Tile::Tile()
{

}

int Tile::GetRow()
{
    return row;
}
int Tile::GetColumn()
{
    return col;
}
int Tile::GetData()
{
    return data;
}
bool Tile::IsSelected()
{
    return selected;
}
sf::Sprite& Tile::GetSprite()
{
    return spr;
}
AnimatedSprite Tile::GetAnimation()
{
    return animatedSprite;
}

void Tile::SetRow(int newRow)
{
    row = newRow;
}
void Tile::SetColumn(int newCol)
{
    col = newCol;
}
void Tile::SetData(int newData)
{
    data = newData;
}
void Tile::SetSelected(bool flag)
{
    selected = flag;
}
void Tile::SetSprite(sf::Sprite newSprite)
{
    spr = newSprite;
}
void Tile::SetAnimation(AnimatedSprite newAnim)
{
    animatedSprite = newAnim;
}
