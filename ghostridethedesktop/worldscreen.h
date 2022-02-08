#ifndef WORLDSCREEN_H
#define WORLDSCREEN_H

#include "screen.h"
#include "backgroundmanager.h"
#include "player.h"
#include "contactlistener.h"

class WorldScreen : public Screen
{
private:

public:
    WorldScreen();
    int Run(b2World& World, BackgroundManager& bgm);
    b2Vec2& GetNewPlayerCoords(ContactListener &cl, b2Vec2 prevCoords);
};

#endif // WORLDSCREEN_H
