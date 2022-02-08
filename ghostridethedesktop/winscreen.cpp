#include "winscreen.h"
#include "SFMLDebugDraw.h"
#include "contactlistener.h"

WinScreen::WinScreen()
{

}

int WinScreen::Run(b2World& World, BackgroundManager& bgm)
{
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "You win!",sf::Style::Close);
    Window.setFramerateLimit(30);
    Window.setMouseCursorVisible(false);
    isRunning = true;
    qDebug() << "Started win Screen" << endl;
    int nextScreen = 0;

    ContactListener cl;
    World.SetContactListener(&cl);

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/win.ogg");

    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    sound1.play();


    QResource background(":images/titleScreenMockup.png");
    sf::Texture backgroundT;
    backgroundT.loadFromMemory(background.data(), background.size());
    sf::Sprite backgroundS;
    backgroundS.setTexture(backgroundT);

    sf::Font font;
    QResource fontbruh(":/computer_pixel-7.ttf");
    font.loadFromMemory(fontbruh.data(), fontbruh.size());

    sf::Text timertext;
    timertext.setString("Mini Game Complete!");
    timertext.setFont(font);
    timertext.setCharacterSize(60);
    timertext.setStyle(sf::Text::Regular);
    timertext.setFillColor(sf::Color::Green);
    timertext.setPosition(200, 200);

    sf::Text minitext;
    minitext.setString("Mini");
    minitext.setFont(font);
    minitext.setCharacterSize(60);
    minitext.setStyle(sf::Text::Regular);
    minitext.setFillColor(sf::Color::Green);

    sf::Text gametext;
    gametext.setString("Game");
    gametext.setFont(font);
    gametext.setCharacterSize(60);
    gametext.setStyle(sf::Text::Regular);
    gametext.setFillColor(sf::Color::Green);

    sf::Text completetext;
    completetext.setString("Complete!");
    completetext.setFont(font);
    completetext.setCharacterSize(60);
    completetext.setStyle(sf::Text::Regular);
    completetext.setFillColor(sf::Color::Green);

    sf::Text EnterToLeavetext;
    EnterToLeavetext.setString("(Press ENTER to leave)");
    EnterToLeavetext.setFont(font);
    EnterToLeavetext.setCharacterSize(30);
    EnterToLeavetext.setStyle(sf::Text::Regular);
    EnterToLeavetext.setFillColor(sf::Color::Green);
    EnterToLeavetext.setPosition(275, 300);

    CreateWinScreenBody(500,37,400,270,World);//ground
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(400/32, 270/32);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = World.CreateBody(&BodyDef);

//    b2PolygonShape Shape;
//    Shape.SetAsBox((500.f/2)/32, (37.f/2)/32);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);

    b2Body* miniBody = CreateWinScreenDBody(80,37,235,250,10,World);//mini
    b2Body* gameBody = CreateWinScreenDBody(100,37,345,250,20,World);//game
    b2Body* completeBody = CreateWinScreenDBody(190,37,505,250,30,World);//complete!

    sf::Clock clock;
    sf::Clock clock2;
    sf::Clock clock3;
    sf::Clock displayClock;
    sf::Clock miniClock;
    sf::Clock gameClock;
    sf::Clock completeClock;
    sf::Clock sparkClock;
    bool showText = false;
    bool miniup,gameup,completeup = false;
    Window.display();
    while (isRunning)
    {
        //qDebug() << "----------------before step--------------------------" << endl;
        World.Step(1.0f/30.f, 8, 3);
        //qDebug() << "----------------after step--------------------------" << endl;
        sf::Event event;
        sf::Time frameTime = clock3.restart();
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                isRunning = false;
                Window.close();
                return -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                isRunning = false;
                Window.close();
                for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
                {
                    World.DestroyBody(BodyIterator);
                }
                nextScreen = 1;
            }
        }
        b2Vec2 vec;
        vec.x = 0;
        vec.y = -(100) * frameTime.asSeconds() * 2;

        if(miniBody->GetLinearVelocity().x == 0 && miniBody->GetLinearVelocity().y == 0)
        {
            miniup = false;
        }
        if(miniClock.getElapsedTime().asMilliseconds() >= 0 && !miniup)
        {
            miniBody->SetLinearVelocity(vec);
            miniup=true;
            miniClock.restart();
        }
        if(gameBody->GetLinearVelocity().x == 0 && gameBody->GetLinearVelocity().y == 0)
        {
            gameup = false;
        }
        if(gameClock.getElapsedTime().asMilliseconds() >= 1000 && !gameup)
        {
            gameBody->SetLinearVelocity(vec);
            gameup=true;
            gameClock.restart();
        }
        if(completeBody->GetLinearVelocity().x == 0 && completeBody->GetLinearVelocity().y == 0)
        {
            completeup = false;
        }
        if(completeClock.getElapsedTime().asMilliseconds() >= 2000 && !completeup)
        {
            completeBody->SetLinearVelocity(vec);
            completeup=true;
            completeClock.restart();
        }

        Window.clear(sf::Color(0, 0, 0));

        Window.draw(backgroundS);
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(660,100));
        rect.setFillColor(sf::Color::Black);
        rect.setPosition(70,200);
        Window.draw(rect);

//        int x1 = 100;
//        int y1 = 100;
//        int x2 = 700;
//        int y2 = 100;
//        int x3 = 100;
//        int y3 = 500;
//        int x4 = 700;
//        int y4 = 500;

        if(sparkClock.getElapsedTime().asMilliseconds() >= 100)
        {
//            CreateSpark(World,x1,y1,clock.getElapsedTime().asMilliseconds());
//            CreateSpark(World,x2,y2,clock.getElapsedTime().asMilliseconds());
//            CreateSpark(World,x3,y3,clock.getElapsedTime().asMilliseconds());
//            CreateSpark(World,x4,y4,clock.getElapsedTime().asMilliseconds());
            sparkClock.restart();
        }

        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if(BodyIterator->GetType() == b2_dynamicBody)
            {
                if(BodyIterator->GetUserData() == (void*)(99999+10))//mini
                {
                    float x = BodyIterator->GetPosition().x*32;
                    float y = BodyIterator->GetPosition().y*32;
                    minitext.setOrigin(35.f,45.f);
                    minitext.setPosition(BodyIterator->GetPosition().x*32,BodyIterator->GetPosition().y*32);
                    Window.draw(minitext);
                }
                else if(BodyIterator->GetUserData() == (void*)(99999+20))//game
                {
                    gametext.setOrigin(43.f,45.f);
                    gametext.setPosition(BodyIterator->GetPosition().x*32,BodyIterator->GetPosition().y*32);
                    Window.draw(gametext);
                }
                else if(BodyIterator->GetUserData() == (void*)(99999+30))//complete
                {
                    completetext.setOrigin(90.f,45.f);
                    completetext.setPosition(BodyIterator->GetPosition().x*32,BodyIterator->GetPosition().y*32);
                    Window.draw(completetext);
                }
                else
                {
                    int bodyCreateTime = (unsigned long)BodyIterator->GetUserData();
                    int clockTime = (clock.getElapsedTime().asMilliseconds() - 2000);
                    if(bodyCreateTime <= clockTime)
                    {
                        World.DestroyBody(BodyIterator);
                    }
                    else
                    {
                        int r = rand()%256;
                        int g = rand()%256;
                        int b = rand()%256;

                        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(16,16));
                        rect.setOrigin(16.f,16.f);
                        rect.setFillColor(sf::Color(r,g,b,200));
                        rect.setPosition(BodyIterator->GetPosition().x,BodyIterator->GetPosition().y);
                        Window.draw(rect);
                    }
                }
            }
        }

        if(clock2.getElapsedTime().asMilliseconds() >= 500)
        {
          showText = true;
        }
        if(showText && displayClock.getElapsedTime().asMilliseconds() <= 1500)
        {
          Window.draw(EnterToLeavetext);
        }
        if(displayClock.getElapsedTime().asMilliseconds() > 1500)
        {
            showText = false;
            clock2.restart();
            displayClock.restart();
        }
        Window.display();
    }

    isRunning = false;
    for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        World.DestroyBody(BodyIterator);
    }
    return nextScreen;
}

void WinScreen::CreateSpark(b2World& World,int x, int y,int createTime)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x, y);
    BodyDef.type = b2_dynamicBody;
    b2Body *Body = World.CreateBody(&BodyDef);
    Body->SetUserData((void*)((int)createTime));

    b2PolygonShape Shape;
    Shape.SetAsBox((16.f/2)/32, (16.f/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    Body->SetGravityScale(0.f);

    int neg = rand()%4;
    if(neg==0)
    {
        Body->SetLinearVelocity(b2Vec2(rand()%50000,rand()%50000));
    }
    else if(neg == 1)
    {
        Body->SetLinearVelocity(b2Vec2(rand()%50000,(-1)*rand()%50000));
    }
    else if(neg == 2)
    {
        Body->SetLinearVelocity(b2Vec2((-1)*rand()%50000,rand()%50000));
    }
    else if(neg == 3)
    {
        Body->SetLinearVelocity(b2Vec2((-1)*rand()%50000,(-1)*rand()%50000));
    }
}

void WinScreen::CreateWinScreenBody(float width, float height, float x, float y, b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x/32, y/32);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width/2)/32, (height/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
}

b2Body* WinScreen::CreateWinScreenDBody(float width, float height, float x, float y,int offset, b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x/32, y/32);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width/2)/32, (height/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.shape = &Shape;
    Body->CreateFixture(&FixtureDef);
    Body->SetUserData((void*)(99999+offset));

    return Body;
}
