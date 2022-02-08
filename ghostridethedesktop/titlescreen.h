#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include "screen.h"

class TitleScreen : public Screen
{
private:
    void CreateSpark(b2World& World,int x, int y,int createTime);
public:
    TitleScreen();
    int Run(b2World& World, BackgroundManager& bgm);
};

#endif // TITLESCREEN_H
