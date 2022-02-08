#include "titlescreen.h"

TitleScreen::TitleScreen()
{

}

int TitleScreen::Run(b2World& World, BackgroundManager& bgm)
{
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Welcome to Ghost Ride The Desktop",sf::Style::Close);
    Window.setFramerateLimit(30);
    Window.setMouseCursorVisible(false);
    isRunning = true;
    qDebug() << "Started title Screen" << endl;
    int nextScreen = 0;

    sf::Texture TitleScreenTexture;
    QResource titleScreenPNG(":/images/titleScreenMockup.png");
    TitleScreenTexture.loadFromMemory(titleScreenPNG.data(), titleScreenPNG.size());
    sf::Texture sparkTexture;
    QResource sparkPNG(":/images/sparks.png");
    sparkTexture.loadFromMemory(sparkPNG.data(), sparkPNG.size());

    sf::SoundBuffer buffer;
    QResource track1(":/sounds/othersong.ogg");
    buffer.loadFromMemory(track1.data(), track1.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    sound1.play();

    sf::Clock clock;
    Window.display();
    clock.restart();
    while (isRunning)
    {
        World.Step(1/60.f, 8, 3);
        sf::Event event;
        int x = sf::Mouse::getPosition(Window).x;
        int y = sf::Mouse::getPosition(Window).y;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                isRunning = false;
                Window.close();
                return -1;
            }
            else if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
            {
                isRunning = false;
                Window.close();
                nextScreen = 8;
            }
        }
        Window.clear();

        sf::Sprite titleSprite;
        titleSprite.setTexture(TitleScreenTexture);
        titleSprite.setOrigin(0, 0);
        titleSprite.setPosition(0,0);
        Window.draw(titleSprite);

        CreateSpark(World,x,y,clock.getElapsedTime().asMilliseconds());
        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if(BodyIterator->GetType() == b2_dynamicBody)
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
        Window.display();
    }
    //sound1.stop();
    for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        World.DestroyBody(BodyIterator);
    }
    isRunning = false;
    return nextScreen;
}

void TitleScreen::CreateSpark(b2World& World,int x, int y,int createTime)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x, y);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);
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
