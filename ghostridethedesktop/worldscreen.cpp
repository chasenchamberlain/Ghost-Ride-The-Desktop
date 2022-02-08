#include "worldscreen.h"
#include <QDebug>
#include "SFMLDebugDraw.h"

WorldScreen::WorldScreen()
{

}

int WorldScreen::Run(b2World& World, BackgroundManager& bgm)
{
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$ Ghost_Ride_The_Desktop.exe", sf::Style::Close);
    SFMLDebugDraw debugDraw(Window);
    Window.setMouseCursorVisible(false);
    World.SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit); //Only draw shapes

    Window.setFramerateLimit(30);
    ContactListener cl;
    World.SetContactListener(&cl);

    isRunning = true;
    qDebug() << "Started world Screen" << endl;
    int nextScreen = 1;

    bgm.CreateRoom(World);

    // Make the player Object.
    b2Vec2 playerCoords = bgm.GetPlayerCoords();
    Player ghost;
    ghost.CreateBody(World, playerCoords.x, playerCoords.y);

    sf::Clock clock;
    sf::Clock bulletClock;

    float speed = ghost.GetPlayerSpeed();
    bool noKeyWasPressed = true;

    //test
    while (isRunning)
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                return -1;
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    // check to see if we are on a game sensor, if we are then change screen.
                    int miniGameScreen = cl.MiniGameLaunched();
                    if(miniGameScreen != 0)
                    {
                        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
                        {
                            World.DestroyBody(BodyIterator);
                        }
                        b2Vec2 previousPlayerCoords(ghost.GetSprite().getPosition().x, ghost.GetSprite().getPosition().y);
                        bgm.SetPlayerCoords(previousPlayerCoords);
                        nextScreen = miniGameScreen;
                        isRunning = false;
                        return miniGameScreen;
                    }
                    if(cl.EndGame())
                    {
                        bgm.gameWon = true;
                        bgm.SetIsWelcome(false);
                        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
                        {
                            World.DestroyBody(BodyIterator);
                        }
                        bgm.SetRoom(cl.getCoord());
                        return 8;
                    }
                }
            }
        }

        World.Step(1/60.f, 8, 3);

        // if a key was pressed set the correct animation and move correctly
        sf::Vector2f movement(0.f, 0.f);
        sf::Time frameTime = clock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            ghost.SetAnimation(A_UP);
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            ghost.SetAnimation(A_DOWN);
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            ghost.SetAnimation(A_LEFT);
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            ghost.SetAnimation(A_RIGHT);
            movement.x += speed;
            noKeyWasPressed = false;
        }

        ghost.Move(movement, frameTime.asSeconds());

        bgm.PlayCurrentAnimation();
        bgm.UpdateCurrentAnimation(frameTime);

        if (noKeyWasPressed)
        {
            ghost.SetAnimation(A_IDLE);
        }
        noKeyWasPressed = true;

        // update AnimatedSprite
        ghost.UpdateAnimation(frameTime);

        b2Vec2 previousPlayerCoords;
        previousPlayerCoords.x = ghost.GetSprite().getPosition().x;
        previousPlayerCoords.y = ghost.GetSprite().getPosition().y;
        // draw
        if(cl.RoomChanged())
        {
            cl.SetRoomChanged(false);
            for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
            {
                World.DestroyBody(BodyIterator);
            }
            bgm.SetRoom(cl.getCoord());
            qDebug() << "player coords before trans x: " << previousPlayerCoords.x << " y: " << previousPlayerCoords.y << endl;
            b2Vec2 playerCoords = GetNewPlayerCoords(cl, previousPlayerCoords);
            if((bgm.GetRoomRow() == 0 && bgm.GetRoomCol() == 1) && (cl.DaveLost()||bgm.lostToDave))
            {
                playerCoords.x = 400;
                playerCoords.y = 300;
                cl.SetDaveLost(false);
                bgm.lostToDave = false;
            }
            ghost.CreateBody(World, playerCoords.x, playerCoords.y);
            bgm.CreateRoom(World);
        }

        bgm.SetSprites();
        ghost.SetSprite();
        Window.clear();

        // Draw world
        vector<sf::Sprite> bgmSprites = bgm.GetSprites();
        for(vector<sf::Sprite>::iterator it = bgmSprites.begin(); it != bgmSprites.end(); ++it)
        {
            Window.draw(*it);
        }
        if(bgm.IsCurrentRoomComplete())
        {
            Window.draw(bgm.currentAnimatedSprite);
        }

        if(cl.MiniGameLaunched() != 0 && !(cl.DaveLost() || bgm.lostToDave))
        {
            // textShader
            sf::RectangleShape textShader(sf::Vector2f(230, 100));
            textShader.setOrigin(0,0);
            textShader.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(110, 125));
            textShader.setFillColor(sf::Color(0,0,0, 215));
            Window.draw(textShader);

            // set and load text
            sf::Font font;
            QResource fontbruh(":/computer_pixel-7.ttf");
            font.loadFromMemory(fontbruh.data(), fontbruh.size());
            sf::Text timertext;
            timertext.setString("Press SPACE to \nenter the game!");
            timertext.setFont(font);
            timertext.setCharacterSize(40);
            timertext.setStyle(sf::Text::Regular);
            timertext.setFillColor(sf::Color::Green);
            timertext.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(100, 125));
            Window.draw(timertext);
        }
        if(cl.EndGame())
        {
            // textShader
            sf::RectangleShape textShader(sf::Vector2f(230, 100));
            textShader.setOrigin(0,0);
            textShader.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(40, 125));
            textShader.setFillColor(sf::Color(0,0,0, 215));
            Window.draw(textShader);

            sf::Font font;
            QResource fontbruh(":/computer_pixel-7.ttf");
            font.loadFromMemory(fontbruh.data(), fontbruh.size());
            sf::Text timertext;
            timertext.setString("Press SPACE to \npick your OS!");
            timertext.setFont(font);
            timertext.setCharacterSize(40);
            timertext.setStyle(sf::Text::Regular);
            timertext.setFillColor(sf::Color::Green);
            timertext.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(30, 125));
            Window.draw(timertext);
        }
        if(!bgm.gameWon && (cl.GetLostCounter() > 0 || bgm.GetLostCounter() > 0)&&!(bgm.GetRoomRow() == 0 && bgm.GetRoomCol() == 0))
        {
            bgm.IncrementCounter();

            sf::RectangleShape textShader(sf::Vector2f(320, 150));
            textShader.setOrigin(0,0);
            textShader.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(160, 170));
            textShader.setFillColor(sf::Color(0,0,0, 215));
            Window.draw(textShader);

            sf::Font font;
            QResource fontbruh(":/computer_pixel-7.ttf");
            font.loadFromMemory(fontbruh.data(), fontbruh.size());
            sf::Text timertext;
            timertext.setString("404 Dave has defeated \nyou! Head back to his\nroom to get your OS!");
            timertext.setFont(font);
            timertext.setCharacterSize(40);
            timertext.setStyle(sf::Text::Regular);
            timertext.setFillColor(sf::Color::Green);
            timertext.setPosition(ghost.GetSprite().getPosition() - sf::Vector2f(150, 170));
            Window.draw(timertext);
        }
        // draw player
        if(bgm.GetRoomRow() == 0 && bgm.GetRoomCol() == 0)
        {
            bgm.moveDave(0.5);
            if(bulletClock.getElapsedTime().asMilliseconds() >= 200)
            {
                 bgm.CreateBullet(World);
                 bulletClock.restart();
            }
            for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
            {
                sf::Font font;
                QResource fontbruh(":/computer_pixel-7.ttf");
                font.loadFromMemory(fontbruh.data(), fontbruh.size());

                sf::Text timertext;

                timertext.setFont(font);
                timertext.setOrigin(16.f,16.f);
                timertext.setCharacterSize(50);
                timertext.setStyle(sf::Text::Regular);
                timertext.setFillColor(sf::Color::Red);

                if(BodyIterator->GetUserData() == (void*)765)
                {
                    timertext.setString("&");
                    timertext.setPosition(BodyIterator->GetPosition().x*32+5,BodyIterator->GetPosition().y*32-25);
                }
                if(BodyIterator->GetUserData() == (void*)766)
                {
                    timertext.setCharacterSize(70);
                    timertext.setString("*");
                    timertext.setPosition(BodyIterator->GetPosition().x*32+10,BodyIterator->GetPosition().y*32-35);
                }
                if(BodyIterator->GetUserData() == (void*)767)
                {
                    timertext.setCharacterSize(50);
                    timertext.setString("->");
                    timertext.setPosition(BodyIterator->GetPosition().x*32,BodyIterator->GetPosition().y*32-25);
                }
                Window.draw(timertext);
            }
        }

        Window.draw(ghost.GetAnimatedSprite());
        //Window.draw(ghost.GetSprite()); // box used for DEBUG
//        World.DrawDebugData();
        Window.display();
    }
    return nextScreen;
}

b2Vec2& WorldScreen::GetNewPlayerCoords(ContactListener &cl, b2Vec2 prevCoords)
{
    b2Vec2 playerCoords(prevCoords.x, prevCoords.y);
    int hTran = 755;
    int vTran = 555;
    switch(cl.GetTransitionType())
    {
    case NONE:
        break;
    case TOP:
        playerCoords.y += vTran;
        break;
    case RIGHT:
        playerCoords.x -= hTran;
        break;
    case BOTTOM:
        playerCoords.y -= vTran;
        break;
    case LEFT:
        playerCoords.x += hTran;
        break;
    }
    qDebug() << "player coords after trans x: " << playerCoords.x << " y: " << playerCoords.y << endl;
    return playerCoords;
}
