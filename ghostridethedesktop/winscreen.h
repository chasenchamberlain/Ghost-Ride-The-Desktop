#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "screen.h"

class WinScreen : public Screen
{
public:
    WinScreen();
    int Run(b2World& World, BackgroundManager& bgm);
    void CreateSpark(b2World& World,int x, int y,int createTime);
    void CreateWinScreenBody(float width, float height, float x, float y, b2World& World);
    b2Body* CreateWinScreenDBody(float width, float height, float x, float y,int offset, b2World& World);
};

#endif // WINSCREEN_H
