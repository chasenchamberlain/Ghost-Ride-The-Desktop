#ifndef SCREEN_H
#define SCREEN_H

#include <QObject>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <QDebug>
#include <QResource>
#include "SFML/Graphics/AnimatedSprite.hpp"
#include "backgroundmanager.h"

class Screen
{
protected:
    bool isRunning = false;
private:

public:
    Screen();
    virtual int Run (b2World& World, BackgroundManager& bgm) = 0;
};

#endif // SCREEN_H
