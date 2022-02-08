#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>
#include <Box2D.h>
#include <SFML/Graphics/Texture.hpp>
#include <QResource>
#include "SFML/Graphics/AnimatedSprite.hpp"
#include <QDebug>
#include "contactlistener.h"
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "player.h"
#include "backgroundmanager.h"
// include screen
#include "screen.h"
// include each screen
#include "titlescreen.h"
#include "worldscreen.h"
#include "minigamescreen.h"
#include "winscreen.h"
#include "infoscreen.h"

#include <vector>
using namespace std;

int main()
{
    /** Prepare the world */
    b2Vec2 Gravity(0.f, 9.8f);
    b2World World(Gravity);

    // Make the background manager
    BackgroundManager bgm;

    vector<Screen*> screens;

    // FOR DEBUGGING YOU CAN SET THE SCREEN YOU WANT TO START WITH
    int screen = 0 ;

    TitleScreen ts; // screen 0
    screens.push_back(&ts);
    WorldScreen ws; // screen 1
    screens.push_back(&ws);
    MiniGameScreen pwr(PWR); // screen 2
    screens.push_back(&pwr);
    MiniGameScreen fan(FAN); // screen 3
    screens.push_back(&fan);
    MiniGameScreen cpu(CPU); // screen 4
    screens.push_back(&cpu);
    MiniGameScreen gpu(GPU); // screen 5
    screens.push_back(&gpu);
    MiniGameScreen ram(RAM); // screen 6
    screens.push_back(&ram);
    WinScreen win;           // screen 7
    screens.push_back(&win);
    InfoScreen info;         // screen 8;
    screens.push_back(&info);

    //Main loop
    while (screen >= 0)
    {
         screen = screens.at(screen)->Run(World, bgm);

    }
    return 0;
}
