#include "minigamescreen.h"
#include "SFMLDebugDraw.h"
#include "player.h"
#include "contactlistener.h"

MiniGameScreen::MiniGameScreen()
{
}

MiniGameScreen::MiniGameScreen(RoomEntity _ID)
{
    switch(_ID)
    {
    case PWR:
        ID = MG_PWR;
        break;
    case FAN:
        ID = MG_FAN;
        break;
    case CPU:
        ID = MG_CPU;
        break;
    case GPU:
        ID = MG_GPU;
        break;
    case RAM:
        ID = MG_RAM;
        break;
    }
    isCleared = false;
}


int MiniGameScreen::Run(b2World& World, BackgroundManager& bgm)
{
    switch(ID)
    {
    case MG_PWR:
        return PowerSupplyGame(World, bgm);
        break;
    case MG_FAN:
        return CoolingGame(World, bgm);
        break;
    case MG_CPU:
        return CPUGame(World, bgm);
        break;
    case MG_GPU:
        return GPUGame(World, bgm);
        break;
    case MG_RAM:
        return RAMGame(World, bgm);
        break;
    }
    return 0;
}

void MiniGameScreen::CreatePowerSupplyBody(float width, float height, float x, float y, bool isSensor, b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x/32, y/32);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width/2)/32, (height/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    if(isSensor)
    {
        FixtureDef.isSensor = true;
        Body->SetUserData((void*)54321);
    }
    Body->CreateFixture(&FixtureDef);
}

void MiniGameScreen::CreatePowerSupplySparks(float width, float height, float x, float y, b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(x/32, y/32);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((width/2)/32, (height/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = true;

    Body->SetUserData((void*)420);
    Body->CreateFixture(&FixtureDef);
}

int MiniGameScreen::PowerSupplyGame(b2World& World, BackgroundManager& bgm)
{
    qDebug() << "Power Supply MiniGame started!" << endl;
    isRunning = true;
    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$ Power_Supply.exe",sf::Style::Close);
    Window.setFramerateLimit(30);

    ContactListener cl;
    cl.isGrounded = true;
    cl.charge = 0;

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/powersupply.ogg");

    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    bgm.currentSong.pause();
    sound1.play();


    World.SetContactListener(&cl);
    SFMLDebugDraw debugDraw(Window);
    World.SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit);
    //**************************************************************
    bgm.CreateWall(World,SOUTH);
    bgm.CreateWall(World,EAST);
    bgm.CreateWall(World,WEST);
    //create the static bodies
    CreatePowerSupplyBody(100,200,400,468,false,World);
    CreatePowerSupplyBody(200,50,132,300,false,World);
    CreatePowerSupplyBody(100,100,600,300,false,World);
    CreatePowerSupplyBody(100,100,718,518,false,World);
    //create the sensors
    CreatePowerSupplyBody(100,1,400,368,true,World);
    CreatePowerSupplyBody(200,1,132,275,true,World);
    CreatePowerSupplyBody(100,1,600,250,true,World);
    CreatePowerSupplyBody(100,1,718,468,true,World);
    CreatePowerSupplyBody(800,1,400,568,true,World);
    //**************************************************************
    sf::Texture groundTexture;
    QResource ground(":/images/psground.png");
    groundTexture.loadFromMemory(ground.data(), ground.size());
    sf::Sprite GroundSprite;
    GroundSprite.setTexture(groundTexture);
    GroundSprite.setPosition(0, 568);

    sf::Texture wallTexture;
    QResource wall(":/images/pswall.png");
    wallTexture.loadFromMemory(wall.data(), wall.size());
    sf::Sprite leftWallSprite;
    leftWallSprite.setTexture(wallTexture);
    leftWallSprite.setPosition(0, 0);
    sf::Sprite rightWallSprite;
    rightWallSprite.setTexture(wallTexture);
    rightWallSprite.setPosition(768, 0);

    sf::Texture guyTexture;
    QResource guy(":/images/battery.png");
    guyTexture.loadFromMemory(guy.data(), guy.size());

    sf::Texture sparkTexture;
    QResource spk(":/images/spark1.png");
    sparkTexture.loadFromMemory(spk.data(), spk.size());

    sf::Texture sqBoxTexture;
    QResource b1(":/images/1b1box.png");
    sqBoxTexture.loadFromMemory(b1.data(),b1.size());
    sf::Sprite leftbox;
    leftbox.setTexture(sqBoxTexture);
    leftbox.setPosition(550, 250);
    sf::Sprite rightbox;
    rightbox.setTexture(sqBoxTexture);
    rightbox.setPosition(668, 468);

    sf::Texture tallBoxTexture;
    QResource b2(":/images/1b2box.png");
    tallBoxTexture.loadFromMemory(b2.data(), b2.size());
    sf::Sprite tallBoxSprite;
    tallBoxSprite.setTexture(tallBoxTexture);
    tallBoxSprite.setPosition(350, 368);

    sf::Texture fatBoxTexture;
    QResource b3(":/images/2b5box.png");
    fatBoxTexture.loadFromMemory(b3.data(), b3.size());
    sf::Sprite fatBoxSprite;
    fatBoxSprite.setTexture(fatBoxTexture);
    fatBoxSprite.setPosition(32, 275);
    //**************************************************************
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(400/32, 300/32);
    BodyDef.type = b2_dynamicBody;
    b2Body* guyBody = World.CreateBody(&BodyDef);
    b2PolygonShape Shape;
    Shape.SetAsBox((32.f/2)/32, (32.f/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 100.f;
    FixtureDef.friction = 4.f;
    FixtureDef.shape = &Shape;
    guyBody->CreateFixture(&FixtureDef);
    guyBody->SetGravityScale(1.f);
    guyBody->SetUserData((void*)4200);
    //**************************************************************
    string s = to_string(cl.charge);
    sf::Font font;
    QResource fontbruh(":/computer_pixel-7.ttf");
    font.loadFromMemory(fontbruh.data(), fontbruh.size());
    sf::Text timertext;
    timertext.setString("charge: "+s);
    timertext.setFont(font);
    timertext.setCharacterSize(60);
    timertext.setStyle(sf::Text::Regular);
    timertext.setFillColor(sf::Color::Black);
    timertext.setPosition(475, 0);

    sf::Text timertext2;
    timertext2.setString("Almost done!");
    timertext2.setFont(font);
    timertext2.setCharacterSize(60);
    timertext2.setStyle(sf::Text::Regular);
    timertext2.setFillColor(sf::Color::Green);
    timertext2.setPosition(475, 100);

    sf::Text timertext3;
    timertext3.setString("Use WASD or the \narrow keys to move!\nGet your charge\n to 500W to win!");
    timertext3.setFont(font);
    timertext3.setCharacterSize(60);
    timertext3.setStyle(sf::Text::Regular);
    timertext3.setFillColor(sf::Color::Yellow);
    timertext3.setPosition(50, 0);
    //**************************************************************
    sf::Clock clock;
    sf::Clock chargeClock;
    sf::Clock textClock;
    float speed = 100.f;
    sf::Vector2f movement(0.f, 0.f);
    while (isRunning)
    {
        if(cl.charge >= 500)
        {
            Window.close();
            isRunning = false;
            qDebug() << "YOU WIN!!!! xD xD xD xD" << endl;
            bgm.SetMiniGameCleared(PWR);
            for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
            {
                World.DestroyBody(BodyIterator);
            }
            return 7;
        }
        World.Step(1/30.f, 8, 3);
        sf::Event event;
        movement.x = 0.f;
        movement.y = 0.f;

        if(chargeClock.getElapsedTime().asMilliseconds() >= 1250)
        {
            int randx = rand()%768;
            if(randx <= 32)
            {
                randx += 32;
            }
            CreatePowerSupplySparks(32,32,randx,50,World);
            chargeClock.restart();
        }

        sf::Time frameTime = clock.restart();
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                isRunning = false;
                return -1;
            }
        }
        //**************************************************************
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
        {
            Window.close();
            isRunning = false;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if(cl.isGrounded)
            {
                movement.y -= speed+70;
                cl.isGrounded = false;
            }
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)  || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            movement.x -= speed;
            if(!cl.isGrounded)
            {
                movement.y += 50;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            movement.x += speed;
            if(!cl.isGrounded)
            {
                movement.y += 50;
            }
        }
        b2Vec2 vec;
        vec.x = movement.x  * frameTime.asSeconds()  * 2;
        vec.y = movement.y * frameTime.asSeconds() * 2;
        if(vec.x != 0.f || vec.y != 0.f)
        {
            guyBody->SetLinearVelocity(vec);
        }
        //**************************************************************
        if((((int)textClock.getElapsedTime().asSeconds())%5) == 0)
        {
            Window.clear(sf::Color::Cyan);
            timertext.setFillColor(sf::Color::Red);
            timertext2.setFillColor(sf::Color::Red);
            timertext3.setFillColor(sf::Color::Red);
        }
        else
        {
            Window.clear(sf::Color::Magenta);
            timertext.setFillColor(sf::Color::Green);
            timertext2.setFillColor(sf::Color::Green);
            timertext3.setFillColor(sf::Color::Green);
        }

        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
        {
            if(BodyIterator->GetUserData() == (void*)420)
            {
                sf::Sprite Sprite;
                Sprite.setTexture(sparkTexture);
                Sprite.setOrigin(16.f, 16.f);
                Sprite.setPosition(32 * BodyIterator->GetPosition().x, 32 * BodyIterator->GetPosition().y);
                Window.draw(Sprite);
            }
        }

        sf::IntRect rect;
        if(cl.charge >=50 && cl.charge <200)
        {
            rect.left=32;
            rect.top=0;
            rect.width=32;
            rect.height=32;
        }
        else if(cl.charge >=200 && cl.charge <400)
        {
            rect.left=64;
            rect.top=0;
            rect.width=32;
            rect.height=32;
        }
        else if(cl.charge >=400 && cl.charge <500)
        {
            rect.left=96;
            rect.top=0;
            rect.width=32;
            rect.height=32;
        }
        else
        {
            rect.left=0;
            rect.top=0;
            rect.width=32;
            rect.height=32;
        }
        sf::Sprite Sprite(guyTexture,rect);
        Sprite.setOrigin(16.f, 16.f);
        Sprite.setPosition(32 * guyBody->GetPosition().x, 32 * guyBody->GetPosition().y);
        Sprite.setRotation(180/b2_pi * guyBody->GetAngle());

        string s = to_string(cl.charge);
        timertext.setString("charge: "+s+" W");

        //World.DrawDebugData();
        Window.draw(Sprite);
        Window.draw(GroundSprite);
        Window.draw(leftWallSprite);
        Window.draw(rightWallSprite);
        Window.draw(leftbox);
        Window.draw(rightbox);
        Window.draw(tallBoxSprite);
        Window.draw(fatBoxSprite);
        Window.draw(timertext);
        if(cl.charge >= 400)
        {
            Window.draw(timertext2);
        }
        if(textClock.getElapsedTime().asSeconds() <= 8)
        {
            Window.draw(timertext3);
        }
        Window.display();
    }
    for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
    {
        World.DestroyBody(BodyIterator);
    }
    return 1;
}

bool MiniGameScreen::CheckFanSolution(int col, int row, int dir, FANTile GameBoard[6][6], sf::Vector2f cpu)
{

    if(col >= 6  || (row < 0 || row >= 6))
    {
        int cpuX = cpu.x / 64 - 1;
        int cpuY = cpu.y / 64 - 1;

            if(row == cpuY && col == cpuX)
            {
                return true;
            }
            else
            {
                return false;
            }
    }

    int currentTileData = GameBoard[row][col].GetData();

    switch(dir)
    {
    case 2: // down
        if(currentTileData == 2)
        {
            row++;
            dir = 2;
        }
        else if (currentTileData == 3)
        {
            col--;
            dir = 4;
        }
        else if (currentTileData == 4)
        {
            col++;
            dir = 6;
        }
        else
        {
            return false;
        }
        break;
    case 4: // left
        if(currentTileData == 1)
        {
            col++;
            dir = 4;
        }
        else if (currentTileData == 3)
        {
            row--;
            dir = 8;
        }
        else if (currentTileData == 6)
        {
            row++;
            dir = 2;
        }
        else
        {
            return false;
        }
        break;
    case 8: // up
        if(currentTileData == 2)
        {
            row--;
            dir = 8;
        }
        else if (currentTileData == 5)
        {
            col++;
            dir = 6;
        }
        else if (currentTileData == 6)
        {
            row++;
            dir = 2;
        }
        else
        {
            return false;
        }
        break;
    case 6: // right
        if(currentTileData == 1)
        {
            col++;
            dir = 6;
        }
        else if (currentTileData == 3)
        {
            row--;
            dir = 8;
        }
        else if (currentTileData == 6)
        {
            row++;
            dir = 2;
        }
        else
        {
            return false;
        }
        break;
    }

    return CheckFanSolution(col, row, dir, GameBoard, cpu);

}

int MiniGameScreen::CoolingGame(b2World& World, BackgroundManager& bgm)
{
    vector<sf::Sprite>sprites;

    int SCALE = 64;

    sf::Texture ScreenTexture;
    QResource pngbitch(":/images/fanbackground.png");
    ScreenTexture.loadFromMemory(pngbitch.data(), pngbitch.size());

    sf::Texture TitleScreenTexture;
    QResource titleScreenPNG(":/images/titleScreenMockup.png");
    TitleScreenTexture.loadFromMemory(titleScreenPNG.data(), titleScreenPNG.size());

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/fan.ogg");
    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    bgm.currentSong.pause();
    sound1.play();

    sf::Sprite titleSprite;

    titleSprite.setTexture(ScreenTexture);
    titleSprite.setOrigin(0, 0);

    sf::Texture question;
    QResource questionPNG(":/images/question.png");
    question.loadFromMemory(questionPNG.data(), questionPNG.size());
    sf::Sprite Sprite;
    Sprite.setTexture(question);


    sf::Texture fanTexture;
    sf::Texture bubTexture;
    QResource fan(":/images/CoolingSystem.png");
    fanTexture.loadFromMemory(fan.data(), fan.size());
    QResource bub(":/images/bubbles.png");
    bubTexture.loadFromMemory(bub.data(), bub.size());
    Animation bubbles;
    Animation fanAnime;
    AnimatedSprite fanPlaying;
    AnimatedSprite waterPlaying;


    fanAnime.setSpriteSheet(fanTexture);
    fanAnime.addFrame(sf::IntRect(0, 0, 128, 128));
    fanAnime.addFrame(sf::IntRect(128, 0, 128, 128));
    fanAnime.addFrame(sf::IntRect(256, 0, 128, 128));
    fanAnime.addFrame(sf::IntRect(384, 0, 128, 128));
    AnimatedSprite fantest(sf::seconds(0.1), true, false);
    fanPlaying = fantest;
    fanPlaying.setPosition(10 * SCALE, 0.f);

    bubbles.setSpriteSheet(bubTexture);
    bubbles.addFrame(sf::IntRect(0, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*2, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*3, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*4, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*5, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*4, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*3, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128*2, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(128, 0, 128, 128));
    bubbles.addFrame(sf::IntRect(0, 0, 128, 128));

    AnimatedSprite bubb(sf::seconds(.2), true, false);
    waterPlaying = bubb;
    waterPlaying.setPosition(640.f , 448.f);


    AnimatedSprite anim;


    isRunning = true;

    FANTile* selected;

    QString fileName(":/gameboards/6x6_COOL1.txt");

    QString board = ReadFile(fileName);
    GameBoard gb = GetRowAndCol(fileName);
    FANTile gameBoard[6][6];
    QStringList symbols = board.split(" ");
    int rowCount = -1;
    for(int i = 0; i < gb.rowNum * gb.colNum; i++)
    {
        int col = i % gb.colNum;
        if(col == 0)
        {
            rowCount++;
        }
        QString symbol = symbols.at(i);
        int data = symbol.at(0).toLatin1() - 48;
        FANTile t(i, col, data, false, true, Sprite, anim);
        gameBoard[rowCount][col] = t;
    }
    selected = &gameBoard[0][0];


    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$ Cooling.exe",sf::Style::Close);
    Window.setMouseCursorVisible(true);
    SFMLDebugDraw debugDraw(Window);
    World.SetDebugDraw(&debugDraw);
    debugDraw.SetFlags(b2Draw::e_shapeBit); //Only draw shapes

    Window.setFramerateLimit(30);

    // -------------- Timer stuff starts here --------------------
    int countdown = 45;
    sf::Clock clock;
    sf::Clock displayClock;
    bool showText = false;


    string s = to_string(countdown);
    sf::Font font;
    QResource fontbruh(":/computer_pixel-7.ttf");
    font.loadFromMemory(fontbruh.data(), fontbruh.size());
    sf::Text timertext;
    timertext.setString(s);
    timertext.setFont(font);
    timertext.setCharacterSize(70);
    timertext.setOrigin(-4,16);
    timertext.setStyle(sf::Text::Regular);
    timertext.setFillColor(sf::Color::White);
    timertext.setPosition(7*64, 0);

    string instruct = "Create a path\nfrom the arrow\nto the CPU chip\nto cool it.";
    sf::Text howto;
    howto.setFont(font);
    howto.setString(instruct);
    howto.setCharacterSize(46);
    howto.setStyle(sf::Text::Regular);
    howto.setFillColor(sf::Color::Green);
    howto.setPosition((8 * SCALE + 4) + 5, 0);

    string instruct2 = "You can swap 2\ntiles by clicking\non them";
    sf::Text howto2;
    howto2.setFont(font);
    howto2.setString((instruct2));
    howto2.setCharacterSize(46);
    howto2.setStyle(sf::Text::Regular);
    howto2.setFillColor(sf::Color::Green);
    howto2.setPosition((8 * SCALE) + 4, (3*SCALE) + 10);

    string instruct3 = "Hit ENTER to cool\nthe CPU before \nthe time runs out!";
    sf::Text howto3;
    howto3.setFont(font);
    howto3.setString((instruct3));
    howto3.setCharacterSize(46);
    howto3.setStyle(sf::Text::Regular);
    howto3.setFillColor(sf::Color::Green);
    howto3.setPosition((8 * SCALE) + 4, 6*SCALE);

    string sad = "The CPU overheated! Sorry my guy\nBetter luck next time!";
    sf::Text lose;
    lose.setFont(font);
    lose.setString((sad));
    lose.setCharacterSize(50);
    lose.setStyle(sf::Text::Regular);
    lose.setFillColor(sf::Color::White);
    lose.setPosition((2 * SCALE - 16), 4*SCALE);

    sf::Text EnterToLeavetext;
    EnterToLeavetext.setString("(Press ENTER to leave)");
    EnterToLeavetext.setFont(font);
    EnterToLeavetext.setCharacterSize(18);
    EnterToLeavetext.setStyle(sf::Text::Regular);
    EnterToLeavetext.setFillColor(sf::Color::White);
    EnterToLeavetext.setPosition(585, 515);

    sf::Texture fansheet;
    QResource sheet(":/images/mockupCoolingSpriteSheet.png");
    fansheet.loadFromMemory(sheet.data(), sheet.size());
    sf::IntRect startRect(384, 0, SCALE, SCALE);
    sf::IntRect cpuRect(448, 0, SCALE, SCALE);

    sf::Sprite cpuSprite(fansheet, cpuRect);
    sf::Sprite startSprite(fansheet, startRect);

    srand(time(NULL)); // Seed the time
    int randPositionY = rand()%(6-1 + 1) + 1;
    int randPositionX = rand()%(6-2 + 1) + 2;
    int randomCase = rand()%(3-1 + 1) + 1;
    qDebug() << "X rand: " << randPositionX << endl;
    qDebug() << "Y rand: " << randPositionY << endl;

    switch (randomCase)
    {
    case 1:
        // top placement
        cpuSprite.setPosition(randPositionX * SCALE, 0 * SCALE);
        break;
    case 2:
        // bottom placement
        cpuSprite.setPosition(randPositionX * SCALE, 7 * SCALE);
        break;
    case 3:
        // right placement
        cpuSprite.setPosition(7 * SCALE, randPositionY * SCALE);
        break;
    }
    sf::Vector2f cpu = cpuSprite.getPosition();

    startSprite.setPosition(0, randPositionY * SCALE);

//    int debug = 1;
//    switch (debug)
//    {
//    case 0:
//        startSprite.setPosition(0, randPosition * SCALE);
//        break;
//    case 1:
//        randPositionX = 5;
//        randPosition = 2;
//        cpuSprite.setPosition(randPositionX * SCALE, 0 * SCALE);
//        startSprite.setPosition(0, randPosition * SCALE);
//        break;
//    case 2:
//        cpuSprite.setPosition(randPositionX * SCALE, 7 * SCALE);
//        break;
//    case 3:
//        cpuSprite.setPosition(7 * SCALE, randPosition * SCALE);
//        break;
//    }



    bool tileSelected;
    int _x, _y;
    bool lost = false;

    sf::Clock animationClock;
    while (isRunning)
    {
        int timer = clock.getElapsedTime().asSeconds();
        if(timer > 0)
        {
            countdown--;
            if(countdown < 10)
            {
                timertext.setFillColor(sf::Color::Red);
            }
            string s = to_string(countdown);
            timertext.setString(s);
            clock.restart();
        }
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                isRunning = false;
                return -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Window.close();
                isRunning = false;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if(lost == true)
                {
                    isRunning = false;
                }
            }
            else if(event.type == event.MouseButtonPressed)
            {
                int x = sf::Mouse::getPosition(Window).x / SCALE;
                int y = sf::Mouse::getPosition(Window).y / SCALE;
                FANTile* clicked = &gameBoard[y - 1][x - 1];
                sf::Sprite clickedSprite;
                clickedSprite = clicked->GetSprite();

                qDebug() << "X: " << x << endl;
                qDebug() << "Y: " << y << endl;

                //if((x <= 6 && x > 0) && (y <= 6 && y > 0))
                if(clickedSprite.getGlobalBounds().contains(sf::Mouse::getPosition(Window).x, sf::Mouse::getPosition(Window).y))
                {
                    //FANTile* clicked = &gameBoard[y - 1][x - 1];
                    if(clicked->CheckHidden())
                    {
                        clicked->SetHiddenFalse();
                    }
                    else
                    {
                        // Checks if has been previously selected
                        if(clicked->IsSelected())
                        {
                            qDebug() << "Has been Previously Selected" << endl;

                            if(x == _x && y == _y)
                            {
                                qDebug() << "Cancel selection" << endl;
                                clicked->SetSelected(false);
                                tileSelected = false;
                                _x = -1;
                                _y = -1;
                            }
                        }
                        // Newly selected tile
                        else if (tileSelected)
                        {

                            qDebug() << "----------------Swap!----------------" << endl;

                            //swap data and texture.
                            sf::Sprite dummySprite;
                            int dummyData;

                            FANTile* forSwap = &gameBoard[_y][_x];
                            dummySprite = (forSwap->GetSprite());
                            dummyData = (forSwap->GetData());
                            qDebug() << "A old data: " << forSwap->GetData() <<endl;
                            qDebug() << "B old data: " << clicked->GetData() << endl;


                            forSwap->SetSprite(clicked->GetSprite());
                            forSwap->SetData(clicked->GetData());

                            clicked->SetSprite(dummySprite);
                            clicked->SetData(dummyData);
                            qDebug() << "A  new data: " << forSwap->GetData() <<endl;
                            qDebug() << "B  new data: " << clicked->GetData() <<endl;

                            clicked->SetSelected(false);
                            forSwap->SetSelected(false);
                            tileSelected = false;
                        }
                        else
                        {
                            selected = clicked;

                            qDebug() << "Newly Selected" << endl;

                            tileSelected = true;
                            clicked->SetSelected(true);
                            _x = x -1;
                            _y = y -1;
                        }
                    }
                }
            }// end of else if for mouse event
            else if(event.type == sf::Event::KeyReleased)
            {
                // User has decided they have a path and they are finished
                if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
                {
                    if(CheckFanSolution(0, (randPositionY - 1), 6, gameBoard, cpu))
                    {
                        bgm.SetMiniGameCleared(FAN);
                        return 7;
                    }
                }
            }
        }// poll event end
        sf::Time frameTime = animationClock.restart();
        if (countdown <= 0)
        {
            lost = true;
            countdown--;
            string s = to_string(countdown);
            timertext.setString(s);

            sf::RectangleShape bg(sf::Vector2f(672, 480));
            bg.setPosition(64, 64);
            bg.setFillColor(sf::Color(0, 0, 200));

            titleSprite.setTexture(TitleScreenTexture);
            Window.clear(sf::Color(0, 0, 0, 200));

            Window.draw(titleSprite);
            Window.draw(bg);
            if(clock.getElapsedTime().asMilliseconds() >= 500)
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
                clock.restart();
                displayClock.restart();
            }
            Window.draw(lose);
            Window.display();
        }
        else
        {

            fanPlaying.play(fanAnime);
            fanPlaying.update(frameTime);
            waterPlaying.play(bubbles);
            waterPlaying.update(frameTime);


            Window.clear(sf::Color(121, 65, 121));

            // shader background
            sf::RectangleShape shader(sf::Vector2f(800, 600));
            shader.setOrigin(0,0);
            shader.setPosition(0,0);
            shader.setFillColor(sf::Color(255, 255, 255, 150));

            sf::RectangleShape clockbackground(sf::Vector2f(64, 64));
            clockbackground.setOrigin(0,0);
            clockbackground.setPosition(448, 0);
            clockbackground.setFillColor(sf::Color(0, 0, 0, 200));

            Window.draw(shader);

            // textShader
            sf::RectangleShape textShader(sf::Vector2f(288, 600));
            textShader.setOrigin(0,0);
            textShader.setPosition(512,0);
            textShader.setFillColor(sf::Color(0,0,0, 175));

            // load selector
            sf::RectangleShape selector(sf::Vector2f(64, 64));
            selector.setOrigin(0,0);
            if(tileSelected)
            {
                selector.setPosition(selected->GetSprite().getPosition());
            }
            else
            {
                selector.setPosition(-64, -64);
            }
            selector.setFillColor(sf::Color(162, 255, 63, 80)); //rgb(162, 255, 63)

            sprites.clear();

            int x = SCALE;
            int y = SCALE;
            for(int i = 0; i < gb.rowNum; i++)
            {
                for(int j = 0; j < gb.colNum; j++)
                {
                    gameBoard[i][j].SetSpriteInformation(x, y);
                    sprites.push_back(gameBoard[i][j].GetSprite());
                    x +=SCALE;
                }
                y+=SCALE;
                x=SCALE;
            }

            sprites.push_back(titleSprite);
            sprites.push_back(cpuSprite);
            sprites.push_back(startSprite);
            Window.draw(fanPlaying);
            Window.draw(waterPlaying);
            Window.draw(selector);
            int i = 0;
            for(vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
            {

                Window.draw(*it);
                i++;
            }
            Window.draw(clockbackground);
            Window.draw(textShader);
            Window.draw(howto);
            Window.draw(howto2);
            Window.draw(howto3);
            Window.draw(timertext);
            Window.display();
        }

    }
    return 1;
}

int MiniGameScreen::CPUGame(b2World& World, BackgroundManager& bgm)
{
    qDebug() << "CPU MiniGame started!" << endl;

    vector<sf::Sprite>sprites;

    sf::Sprite Sprite;

    AnimatedSprite anim;

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/cpu.ogg");

    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    bgm.currentSong.pause();

    sound1.play();


    isRunning = true;

    //Build a board of sprites
    QString fileName(":/gameboards/3x3_GPU1.txt");
    QString board = ReadFile(fileName);
    GameBoard gb = GetRowAndCol(fileName);
    CPUTile gameBoard[3][3];
    QStringList symbols = board.split(" ");
    int rowCount = -1;

    for(int i = 0; i < 9; i++)
    {
        QString symbol = symbols.at(i);
        int data = symbol.at(0).toLatin1() - 48;
        if(data == 1)
        {
            CPUTile t(0, 0, data, false, Sprite);
            gameBoard[0][0] = t;
        }
        if(data == 2)
        {
            CPUTile t(0, 1, data, false, Sprite);
            gameBoard[0][1] = t;
        }
        if(data == 3)
        {
            CPUTile t(0, 2, data, false, Sprite);
            gameBoard[0][2] = t;
        }
        if(data == 4)
        {
            CPUTile t(1, 0, data, false, Sprite);
            gameBoard[1][0] = t;
        }
        if(data == 5)
        {
            CPUTile t(1, 1, data, false, Sprite);
            gameBoard[1][1] = t;
        }
        if(data == 6)
        {
            CPUTile t(1, 2, data, false, Sprite);
            gameBoard[1][2] = t;
        }
        if(data == 7)
        {
            CPUTile t(2, 0, data, false, Sprite);
            gameBoard[2][0] = t;
        }
        if(data == 8)
        {
            CPUTile t(2, 1, data, false, Sprite);
            gameBoard[2][1] = t;
        }
        if(data == 9)
        {
            CPUTile t(2, 2, data, false, Sprite);
            gameBoard[2][2] = t;
        }
        //data++;
    }

    sf::RenderWindow Window(sf::VideoMode(800, 700, 32), "[ghost@UofU/terminal ~]$ CPU.exe",sf::Style::Close);
    Window.setMouseCursorVisible(true);
    sf::Font font;
    QResource fontbruh(":/computer_pixel-7.ttf");
    font.loadFromMemory(fontbruh.data(), fontbruh.size());

    sf::Text nextText;
    nextText.setString("Next");
    nextText.setFont(font);
    nextText.setCharacterSize(60);
    nextText.setStyle(sf::Text::Regular);
    nextText.setFillColor(sf::Color::Black);
    nextText.setPosition(690, 630);

    sf::Text questionText;
    questionText.setFont(font);
    questionText.setCharacterSize(50);
    questionText.setStyle(sf::Text::Regular);
    questionText.setFillColor(sf::Color::Black);

    int questionNumber = 1;

    vector<int> tilesSelected;

    while(isRunning)
    {
        while(questionNumber <= 6)
        {
        questionText.setString(QuestionText(questionNumber));
        if(questionNumber == 1)
        {
           questionText.setPosition(35, 20);
        }
        if(questionNumber == 2)
        {
            questionText.setPosition(240, 20);
        }
        else if(questionNumber == 3)
        {
            questionText.setPosition(230, 20);
        }
        else if(questionNumber == 4)
        {
            questionText.setPosition(50, 20);
            questionText.setCharacterSize(45);
        }
        else if(questionNumber == 5)
        {
            questionText.setPosition(240, 20);
            questionText.setCharacterSize(50);
        }
        else if(questionNumber == 6)
        {
            questionText.setPosition(80, 20);
        }
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                isRunning = false;
                return -1;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                Window.close();
                isRunning = false;
                return 1;
            }
            else if((event.type == sf::Event::MouseButtonReleased))
            {
                int relPosX = sf::Mouse::getPosition(Window).x + 100;
                int relPosY = sf::Mouse::getPosition(Window).y + 100;
                int x = relPosX / 186.667;
                int y = relPosY / 188.333;

                qDebug() << "X: " << x << endl;
                qDebug() << "Y: " << y << endl;


                if((x <= 3 && x > 0) && (y <= 3 && y > 0))
                {
                    CPUTile* clicked = &gameBoard[y - 1][x - 1];
                    if(clicked->CheckClicked())
                    {
                        clicked->SetClickedFalse();
                        for( std::vector<int>::iterator iter = tilesSelected.begin(); iter != tilesSelected.end(); ++iter )
                        {
                            if( *iter == clicked->GetData())
                            {
                                tilesSelected.erase(iter);
                                break;
                            }
                        }

                    }
                    else
                    {
                        clicked->SetClickedTrue();
                        tilesSelected.push_back(clicked->GetData());
                    }

                    std::sort(tilesSelected.begin(), tilesSelected.end());

                }
                else if(x == 4 && y == 4)
                {
                    if(questionNumber == 6)
                    {
                        questionNumber = 1;
                    }
                    else if(tilesSelected == QuestionAnswers(questionNumber))
                    {
                         if(questionNumber == 5)
                         {
                             Window.close();
                             isRunning = false;
                             bgm.SetMiniGameCleared(CPU);
                             return 7;
                         }
                         else
                         {
                             questionNumber++;
                         }
                    }
                    else
                    {
                        questionNumber = 6;
                    }

                      for(int i = 0; i < 3; i++)
                      {
                          for (int j = 0; j < 3; j++)
                          {
                            CPUTile* temp = &gameBoard[i][j];
                            temp->SetClickedFalse();
                          }
                      }
                    tilesSelected.clear();
                }
           }

      }

        Window.clear(sf::Color(176,196,222));
        sprites.clear();
        int x = 100;
        int y = 100;

        for(int i = 0; i < gb.rowNum; i++)
        {
            for(int j = 0; j < gb.colNum; j++)
            {
                gameBoard[i][j].SetSpriteInformation(x, y);
                sprites.push_back(gameBoard[i][j].GetSprite());
                x +=186.667;
            }
            y+=188.333;
            x=100;
        }

        int i = 0;
        for(vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
        {
            Window.draw(*it);
            i++;
        }
        Window.draw(nextText);
        Window.draw(questionText);
        Window.display();

     }

        return 7;
    }

    return 1;
}

string MiniGameScreen::QuestionText(int questionNumber)
{
   string resultQuestion = "";

   switch (questionNumber)
   {

   case 1:
     resultQuestion.append("Which Three Numbers are Factors of 15?");
     break;

   case 2:
     resultQuestion.append("What is 16 % 5?");
     break;

   case 3:
     resultQuestion.append("What is (4/3) * 8?");
     break;

   case 4:
     resultQuestion.append("Pick the numbers that are perfect squares");
     break;

   case 5:
     resultQuestion.append("What is 23/3?");
     break;

   case 6:
       resultQuestion.append("Your CPU Could Not Be Configured!!!");
       break;
   }

   return resultQuestion;
}

vector<int> MiniGameScreen::QuestionAnswers(int questionNumber)
{
   vector<int> resultAnswer;;

   switch (questionNumber)
   {

   case 1:
     resultAnswer.push_back(1);
     resultAnswer.push_back(3);
     resultAnswer.push_back(5);
     break;

   case 2:
     resultAnswer.push_back(1);
     break;

   case 3:
     resultAnswer.push_back(8);
     break;

   case 4:
     resultAnswer.push_back(1);
     resultAnswer.push_back(4);
     resultAnswer.push_back(9);
     break;

   case 5:
     resultAnswer.push_back(7);
     break;
   }

   return resultAnswer;
}

sf::RectangleShape MiniGameScreen::DrawSelected(int tileNum)
{
    int x;
    int y;

    switch(tileNum)
    {
    case 1:
        x = 90;
        y = 85;
        break;
    case 2:
        x = 245;
        y = 85;
        break;
    case 3:
        x = 402;
        y = 85;
        break;
    case 4:
        x = 90;
        y = 242;
        break;
    case 5:
        x = 245;
        y = 242;
        break;
    case 6:
        x = 402;
        y = 242;
        break;
    case 7:
        x = 90;
        y = 398;
        break;
    case 8:
        x = 245;
        y = 398;
        break;
    case 9:
        x = 402;
        y = 398;
        break;
    }

    sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(162,162));
    rect.setOrigin(16.f,16.f);
    rect.setFillColor(sf::Color::Yellow);
    rect.setPosition(x,y);
    return rect;
}

bool checkWin(GPUTile gameBoard[3][3])
{
    int correctCount = 0;
    int iterCount = 1;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(gameBoard[i][j].imageIndex == iterCount)
            {
                correctCount++;
            }
            iterCount++;
        }
    }

    if(correctCount == 9)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool swapTiles(int tileNum, GPUTile gameBoard[3][3])
{
    GPUTile temp1;
    GPUTile temp2;
    switch(tileNum)
    {
    case 1:
         temp1 = gameBoard[0][0];
        if(gameBoard[0][1].imageIndex == 9)
        {
            temp2 = gameBoard[0][1];
            gameBoard[0][0] = temp2;
            gameBoard[0][1] = temp1;
            return true;
        }
        else if(gameBoard[1][0].imageIndex == 9)
        {
            temp2 = gameBoard[1][0];
            gameBoard[0][0] = temp2;
            gameBoard[1][0] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 2:
        temp1 = gameBoard[0][1];
        if(gameBoard[0][0].imageIndex == 9)
        {
            temp2 = gameBoard[0][0];
            gameBoard[0][1] = temp2;
            gameBoard[0][0] = temp1;
            return true;
        }
        else if(gameBoard[0][2].imageIndex == 9)
        {
            temp2 = gameBoard[0][2];
            gameBoard[0][1] = temp2;
            gameBoard[0][2] = temp1;
            return true;
        }
        else if(gameBoard[1][1].imageIndex == 9)
        {
            temp2 = gameBoard[1][1];
            gameBoard[0][1] = temp2;
            gameBoard[1][1] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 3:
        temp1 = gameBoard[0][2];
        if(gameBoard[0][1].imageIndex == 9)
        {
            temp2 = gameBoard[0][1];
            gameBoard[0][2] = temp2;
            gameBoard[0][1] = temp1;
            return true;
        }
        else if(gameBoard[1][2].imageIndex == 9)
        {
            temp2 = gameBoard[1][2];
            gameBoard[0][2] = temp2;
            gameBoard[1][2] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 4:
        temp1 = gameBoard[1][0];
        if(gameBoard[1][1].imageIndex == 9)
        {
            temp2 = gameBoard[1][1];
            gameBoard[1][0] = temp2;
            gameBoard[1][1] = temp1;
            return true;
        }
        else if(gameBoard[0][0].imageIndex == 9)
        {
            temp2 = gameBoard[0][0];
            gameBoard[1][0] = temp2;
            gameBoard[0][0] = temp1;
            return true;
        }
        else if(gameBoard[2][0].imageIndex == 9)
        {
            temp2 = gameBoard[2][0];
            gameBoard[1][0] = temp2;
            gameBoard[2][0] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 5:
        temp1 = gameBoard[1][1];
        if(gameBoard[1][0].imageIndex == 9)
        {
            temp2 = gameBoard[1][0];
            gameBoard[1][1] = temp2;
            gameBoard[1][0] = temp1;
            return true;
        }
        else if(gameBoard[0][1].imageIndex == 9)
        {
            temp2 = gameBoard[0][1];
            gameBoard[1][1] = temp2;
            gameBoard[0][1] = temp1;
            return true;
        }
        else if(gameBoard[2][1].imageIndex == 9)
        {
            temp2 = gameBoard[2][1];
            gameBoard[1][1] = temp2;
            gameBoard[2][1] = temp1;
            return true;
        }
        else if(gameBoard[1][2].imageIndex == 9)
        {
            temp2 = gameBoard[1][2];
            gameBoard[1][1] = temp2;
            gameBoard[1][2] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 6:
        temp1 = gameBoard[1][2];
        if(gameBoard[1][1].imageIndex == 9)
        {
            temp2 = gameBoard[1][1];
            gameBoard[1][2] = temp2;
            gameBoard[1][1] = temp1;
            return true;
        }
        else if(gameBoard[0][2].imageIndex == 9)
        {
            temp2 = gameBoard[0][2];
            gameBoard[1][2] = temp2;
            gameBoard[0][2] = temp1;
            return true;
        }
        else if(gameBoard[2][2].imageIndex == 9)
        {
            temp2 = gameBoard[2][2];
            gameBoard[1][2] = temp2;
            gameBoard[2][2] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 7:
        temp1 = gameBoard[2][0];
        if(gameBoard[1][0].imageIndex == 9)
        {
            temp2 = gameBoard[1][0];
            gameBoard[2][0] = temp2;
            gameBoard[1][0] = temp1;
            return true;
        }
        else if(gameBoard[2][1].imageIndex == 9)
        {
            temp2 = gameBoard[2][1];
            gameBoard[2][0] = temp2;
            gameBoard[2][1] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 8:
        temp1 = gameBoard[2][1];
        if(gameBoard[2][0].imageIndex == 9)
        {
            temp2 = gameBoard[2][0];
            gameBoard[2][1] = temp2;
            gameBoard[2][0] = temp1;
            return true;
        }
        else if(gameBoard[1][1].imageIndex == 9)
        {
            temp2 = gameBoard[1][1];
            gameBoard[2][1] = temp2;
            gameBoard[1][1] = temp1;
            return true;
        }
        else if(gameBoard[2][2].imageIndex == 9)
        {
            temp2 = gameBoard[2][2];
            gameBoard[2][1] = temp2;
            gameBoard[2][2] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    case 9:
        temp1 = gameBoard[2][2];
        if(gameBoard[2][1].imageIndex == 9)
        {
            temp2 = gameBoard[2][1];
            gameBoard[2][2] = temp2;
            gameBoard[2][1] = temp1;
            return true;
        }
        else if(gameBoard[1][2].imageIndex == 9)
        {
            temp2 = gameBoard[1][2];
            gameBoard[2][2] = temp2;
            gameBoard[1][2] = temp1;
            return true;
        }
        else
        {
            return false;
        }
        break;
    }


    return false;
}

int MiniGameScreen::GPUGame(b2World& World, BackgroundManager& bgm)
{
    qDebug() << "GPU MiniGame started!" << endl;
    vector<sf::Sprite>sprites;
    sf::Sprite Sprite;
    int selected = 5;

    sf::Texture winTexture;
    QResource gpu(":/images/FlightOfTheRedBaron.png");
    winTexture.loadFromMemory(gpu.data(), gpu.size());

    Animation win;
    AnimatedSprite winPlaying;

    win.setSpriteSheet(winTexture);
    win.addFrame(sf::IntRect(0, 0, 450, 450));
    win.addFrame(sf::IntRect(450, 0, 450, 450));
    win.addFrame(sf::IntRect(450*2, 0, 450, 450));
    win.addFrame(sf::IntRect(450*3, 0, 450, 450));
    win.addFrame(sf::IntRect(450*4, 0, 450, 450));
    win.addFrame(sf::IntRect(450*5, 0, 450, 450));
    win.addFrame(sf::IntRect(450*6, 0, 450, 450));
    win.addFrame(sf::IntRect(450*7, 0, 450, 450));
    win.addFrame(sf::IntRect(450*8, 0, 450, 450));
    win.addFrame(sf::IntRect(450*9, 0, 450, 450));
    win.addFrame(sf::IntRect(450*10, 0, 450, 450));
    win.addFrame(sf::IntRect(450*10, 0, 450, 450));
    win.addFrame(sf::IntRect(450*11, 0, 450, 450));
    win.addFrame(sf::IntRect(450*11, 0, 450, 450));
    win.addFrame(sf::IntRect(450*10, 0, 450, 450));
    win.addFrame(sf::IntRect(450*10, 0, 450, 450));
    win.addFrame(sf::IntRect(450*11, 0, 450, 450));
    win.addFrame(sf::IntRect(450*11, 0, 450, 450));
    AnimatedSprite fantest(sf::seconds(0.1), true, false);
    winPlaying = fantest;
    winPlaying.setPosition(80.f, 75.f);

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/gpu.ogg");

    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    bgm.currentSong.pause();

    sound1.play();

    isRunning = true;

    //Build a board of sprites
    QString fileName(":/gameboards/3x3_GPU1.txt");
    QString board = ReadFile(fileName);
    GameBoard gb = GetRowAndCol(fileName);
    GPUTile gameBoard[3][3];
    QStringList symbols = board.split(" ");
    int rowCount = -1;
    for(int i = 0; i < 9; i++)
    {
        QString symbol = symbols.at(i);
        int data = symbol.at(0).toLatin1() - 48;
        if(data == 1)
        {
            GPUTile t(2, 0, data, true, Sprite);
            gameBoard[2][0] = t;
        }
        if(data == 2)
        {
            GPUTile t(0, 1, data, false, Sprite);
            gameBoard[0][1] = t;
        }
        if(data == 3)
        {
            GPUTile t(2, 1, data, false, Sprite);
            gameBoard[2][1] = t;
        }
        if(data == 4)
        {
            GPUTile t(1, 1, data, false, Sprite);
            gameBoard[1][1] = t;
        }
        if(data == 5)
        {
            GPUTile t(0, 0, data, false, Sprite);
            gameBoard[0][0] = t;
        }
        if(data == 6)
        {
            GPUTile t(2, 2, data, false, Sprite);
            gameBoard[2][2] = t;
        }
        if(data == 7)
        {
            GPUTile t(1, 0, data, false, Sprite);
            gameBoard[1][0] = t;
        }
        if(data == 8)
        {
            GPUTile t(0, 2, data, false, Sprite);
            gameBoard[0][2] = t;
        }
        if(data == 9)
        {
            GPUTile t(1, 2, data, false, Sprite);
            gameBoard[1][2] = t;
        }
    }

    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$ GPU.exe",sf::Style::Close);
    Window.setMouseCursorVisible(true);

    bool winner = false;
    sf::Clock clock;
    sf::Clock animationClock;
    bool showText = false;

    while(isRunning)
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                isRunning = false;
                return -1;
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Space)
                {
                    swapTiles(selected, gameBoard);

                    if(checkWin(gameBoard))
                    {
                        bgm.SetMiniGameCleared(GPU);
                        winner = true;
                    }
                }
                else if(event.key.code == sf::Keyboard::Return)
                {
                    if(winner)
                    {
                        return 7;
                    }
                }

                else if(event.key.code == sf::Keyboard::Escape)
                {
                    Window.close();
                    isRunning = false;
                    return 1;
                }
                else if(event.key.code == sf::Keyboard::C)
                {
                    bgm.SetMiniGameCleared(GPU);
                    winner = true;
                }
                else if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    qDebug() << "Move selected UP" << endl;
                    if(selected == 4)
                    {
                        selected = 1;
                    }
                    else if(selected == 5)
                    {
                        selected = 2;

                    }
                    else if(selected == 6)
                    {
                        selected = 3;

                    }
                    else if(selected == 7)
                    {
                        selected = 4;
                    }
                    else if(selected == 8)
                    {
                        selected = 5;
                    }
                    else if(selected == 9)
                    {
                        selected = 6;
                    }
                }
                else if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    qDebug() << "Move selected LEFT" << endl;
                    if(selected == 2)
                    {
                        selected = 1;
                    }
                    else if(selected == 5)
                    {
                        selected = 4;

                    }
                    else if(selected == 8)
                    {
                        selected = 7;

                    }
                    else if(selected == 3)
                    {
                        selected = 2;
                    }
                    else if(selected == 6)
                    {
                        selected = 5;
                    }
                    else if(selected == 9)
                    {
                        selected = 8;
                    }
                }
                else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    qDebug() << "Move selected DOWN" << endl;
                    if(selected == 1)
                    {
                        selected = 4;
                    }
                    else if(selected == 2)
                    {
                        selected = 5;

                    }
                    else if(selected == 3)
                    {
                        selected = 6;

                    }
                    else if(selected == 4)
                    {
                        selected = 7;
                    }
                    else if(selected == 5)
                    {
                        selected = 8;
                    }
                    else if(selected == 6)
                    {
                        selected = 9;
                    }
                }
                else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    qDebug() << "Move selected RIGHT" << endl;
                    if(selected == 1)
                    {
                        selected = 2;
                    }
                    else if(selected == 4)
                    {
                        selected = 5;

                    }
                    else if(selected == 7)
                    {
                        selected = 8;

                    }
                    else if(selected == 2)
                    {
                        selected = 3;
                    }
                    else if(selected == 5)
                    {
                        selected = 6;
                    }
                    else if(selected == 8)
                    {
                        selected = 9;
                    }
                }
            }

        }

        sf::Time frameTime = animationClock.restart();
        if (winner)
        {
            Window.clear(sf::Color(255,255,255));
            sprites.clear();

            winPlaying.play(win);
            winPlaying.update(frameTime);


            // shader background
            sf::RectangleShape shader(sf::Vector2f(800, 600));
            shader.setOrigin(0,0);
            shader.setPosition(0,0);
            shader.setFillColor(sf::Color(255, 255, 255, 150));
            Window.draw(shader);

            // textShader
            sf::RectangleShape textShader(sf::Vector2f(300, 600));
            textShader.setOrigin(0,0);
            textShader.setPosition(600,0);
            textShader.setFillColor(sf::Color(0,0,0, 200));
            Window.draw(textShader);

            // set and load text
            sf::Font font;
            QResource fontbruh(":/computer_pixel-7.ttf");
            font.loadFromMemory(fontbruh.data(), fontbruh.size());
            sf::Text timertext;
            timertext.setString("Hit Enter\n to Exit.");
            timertext.setFont(font);
            timertext.setCharacterSize(40);
            timertext.setStyle(sf::Text::Regular);
            timertext.setFillColor(sf::Color::Green);
            timertext.setPosition(610, 0);
            Window.draw(timertext);
            Window.draw(winPlaying);
            Window.display();
        }
        else
        {
            Window.clear(sf::Color(255,255,255));
            sprites.clear();

            sf::RectangleShape rect = DrawSelected(selected);
            Window.draw(rect);

            int x = 80;
            int y = 75;
            for(int i = 0; i < gb.rowNum; i++)
            {
                for(int j = 0; j < gb.colNum; j++)
                {
                    gameBoard[i][j].SetSpriteInformation(x, y);
                    sprites.push_back(gameBoard[i][j].GetSprite());
                    x +=156;
                }
                y+=156;
                x=80;
            }

            // shader background
            sf::RectangleShape shader(sf::Vector2f(800, 600));
            shader.setOrigin(0,0);
            shader.setPosition(0,0);
            shader.setFillColor(sf::Color(255, 255, 255, 150));
            Window.draw(shader);

            // textShader
            sf::RectangleShape textShader(sf::Vector2f(300, 600));
            textShader.setOrigin(0,0);
            textShader.setPosition(600,0);
            textShader.setFillColor(sf::Color(0,0,0, 200));
            Window.draw(textShader);

            // set and load text
            sf::Font font;
            QResource fontbruh(":/computer_pixel-7.ttf");
            font.loadFromMemory(fontbruh.data(), fontbruh.size());
            sf::Text timertext;
            timertext.setString("Complete\nthe sliding\ntile puzzle!\n\nUse WASD or \nArrow Keys to \nmove. \n\nUse SPACE to \nslide a tile.");
            timertext.setFont(font);
            timertext.setCharacterSize(40);
            timertext.setStyle(sf::Text::Regular);
            timertext.setFillColor(sf::Color::Green);
            timertext.setPosition(610, 0);
            Window.draw(timertext);

            int i = 0;
            for(vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
            {
                Window.draw(*it);
                i++;
            }
            World.DrawDebugData();
            Window.display();
        }
    }
    return 7;
}

int MiniGameScreen::RAMGame(b2World& World, BackgroundManager& bgm)
{
    qDebug() << "RAM MiniGame started!" << endl;

    vector<sf::Sprite>sprites;

    sf::Sprite Sprite;

    AnimatedSprite anim;

    RAMTile* selected;

    sf::SoundBuffer buffer;
    QResource poo(":/sounds/ram.ogg");

    buffer.loadFromMemory(poo.data(), poo.size());
    sf::Sound sound1;
    sound1.setBuffer(buffer);
    sound1.setLoop(true);
    bgm.soundHappy.pause();
    bgm.soundSpooky.pause();
    bgm.currentSong.pause();

    sound1.play();

    isRunning = true;

    QString fileName(":/gameboards/4x4_RAM1.txt");

    QString board = ReadFile(fileName);
    GameBoard gb = GetRowAndCol(fileName);
    RAMTile gameBoard[4][4]; // change later to be a vector so we can load in diff files.
    QStringList symbols = board.split(" ");
    int rowCount = -1;
    for(int i = 0; i < gb.rowNum * gb.colNum; i++)
    {
        int col = i % gb.colNum;
        if(col == 0)
        {
            rowCount++;
        }
        QString symbol = symbols.at(i);
        int data = symbol.at(0).toLatin1() - 48;
        if(i == 0)
        {
            RAMTile t(rowCount, col, data, Sprite, anim);
            gameBoard[rowCount][col] = t;
        }
        else
        {
            RAMTile t(rowCount, col, data, Sprite, anim);
            gameBoard[rowCount][col] = t;
        }
    }
    selected = &gameBoard[0][0];
    selected->SetSelected(true);
    selected->SetTexture();

    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$ RAM.exe",sf::Style::Close);
    Window.setFramerateLimit(30);
    Window.setMouseCursorVisible(false);

    RAMTile* potentialMatch;
    int numFlipped = 0;
    int progress = 0;
    while (isRunning)
    {
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Window.close();
                isRunning = false;
                return -1;
            }
            else if(event.type == sf::Event::KeyReleased)
            {
                if(event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space)
                {
                    // GAME LOGIC.
                    // flip piece, set num of selected tiles to 1, store the data for it.
                    // next enter, check to see if tile is flipped, if it is, just flip it and reset selected tiles to 1
                    // if it isn't flipped, flip it and then check its data. Leave it flipped
                    // until the user clicks another button
                    if(!selected->isFlipped())
                    {
                        qDebug() << "Flip tile" << endl;
                        selected->Flip();
                        selected->SetSelected(false);
                        selected->SetTexture();
                        if(numFlipped++ > 0)
                        {
                            // check to see if they are equal.
                            if(potentialMatch->GetData() != selected->GetData())
                            {
                                qDebug() << "----------------------NO MATCH------------------" << endl;
//                                potentialMatch->Flip();
//                                selected->Flip();
                                selected->SetSelected(false);
                                selected->SetTexture();
                            }
                            else
                            {
                                qDebug() << "!!!!!!!!!!!!!!MATCH!!!!!!!!!!!!!!!!!" << endl;
                                potentialMatch->Match();
                                selected->Match();
                                progress++;
                            }
                            numFlipped = 0;
                        }
                        else
                        {
                            potentialMatch = selected;
                        }
                    }

                }
                else if(event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up)
                {
                    qDebug() << "Move selected UP" << endl;
                    RAMTile *t = selected->GetRow() - 1 >= 0 ? &gameBoard[selected->GetRow() - 1][selected->GetColumn()] : &gameBoard[gb.rowNum - 1][selected->GetColumn()];
                    t->SetSelected(true);
                    t->SetTexture();
                    if(selected->isFlipped() && !selected->isMatched())
                    {
                        potentialMatch->Flip();
                        selected->Flip();
                    }
                    selected->SetSelected(false);
                    selected->SetTexture();
                    selected = t;
                }
                else if(event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left)
                {
                    qDebug() << "Move selected LEFT" << endl;
                    RAMTile *t = selected->GetColumn() - 1 >= 0 ? &gameBoard[selected->GetRow()][selected->GetColumn() - 1] : &gameBoard[selected->GetRow()][gb.colNum - 1];
                    t->SetSelected(true);
                    t->SetTexture();
                    if(selected->isFlipped() && !selected->isMatched())
                    {
                        potentialMatch->Flip();
                        selected->Flip();
                    }
                    selected->SetSelected(false);
                    selected->SetTexture();
                    selected = t;
                }
                else if(event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                {
                    qDebug() << "Move selected DOWN" << endl;
                    RAMTile* t = selected->GetRow() + 1 < gb.rowNum ? &gameBoard[selected->GetRow()+1][selected->GetColumn()] : &gameBoard[0][selected->GetColumn()];
                    t->SetSelected(true);
                    t->SetTexture();
                    if(selected->isFlipped() && !selected->isMatched())
                    {
                        potentialMatch->Flip();
                        selected->Flip();
                    }
                    selected->SetSelected(false);
                    selected->SetTexture();
                    selected = t;
                }
                else if(event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                {
                    qDebug() << "Move selected RIGHT" << endl;
                    RAMTile *t = selected->GetColumn() + 1 < gb.colNum ? &gameBoard[selected->GetRow()][selected->GetColumn() + 1] : &gameBoard[selected->GetRow()][0];
                    t->SetSelected(true);
                    t->SetTexture();
                    if(selected->isFlipped() && !selected->isMatched())
                    {
                        potentialMatch->Flip();
                        selected->Flip();
                    }
                    selected->SetSelected(false);
                    selected->SetTexture();
                    selected = t;
                }
            }


        }

        if(progress == gb.colNum * gb.rowNum / 2)
        {
            qDebug() << "YOU WIN!!!! :D :D :D :D" << endl;
            // set RAM minigame to clear in bgm
            bgm.SetMiniGameCleared(RAM);
            return 7;
        }

        Window.clear(sf::Color(173,216,230));

        QResource bck(":/images/RAM.png");
        sf::Texture background;
        background.loadFromMemory(bck.data(), bck.size());
        background.setRepeated(true);
        sf::Sprite backgrnd(background, sf::IntRect(0,0,800,600));
        Window.draw(backgrnd);

        // shader background
        sf::RectangleShape shader(sf::Vector2f(800, 600));
        shader.setOrigin(0,0);
        shader.setPosition(0,0);
        shader.setFillColor(sf::Color(255, 255, 255, 150));
        Window.draw(shader);

        // textShader
        sf::RectangleShape textShader(sf::Vector2f(300, 600));
        textShader.setOrigin(0,0);
        textShader.setPosition(590,0);
        textShader.setFillColor(sf::Color(0,0,0, 200));
        Window.draw(textShader);

        // load selector
        sf::RectangleShape selector(sf::Vector2f(145, 145));
        selector.setOrigin(0,0);
        selector.setPosition(selected->GetSprite().getPosition() - sf::Vector2f(8, 8));
        selector.setFillColor(sf::Color(162, 255, 63, 140)); //rgb(162, 255, 63)
        Window.draw(selector);

        // set and load text
        sf::Font font;
        QResource fontbruh(":/computer_pixel-7.ttf");
        font.loadFromMemory(fontbruh.data(), fontbruh.size());
        sf::Text timertext;
        timertext.setString("Find all the \nmatches!\n\nUse WASD or \nArrow Keys to \nmove. \n\nUse SPACE to \nflip a tile.");
        timertext.setFont(font);
        timertext.setCharacterSize(40);
        timertext.setStyle(sf::Text::Regular);
        timertext.setFillColor(sf::Color::Green);
        timertext.setPosition(600, 0);
        Window.draw(timertext);


        sprites.clear();
        for(int i = 0; i < gb.rowNum; i++)
        {
            for(int j = 0; j < gb.colNum; j++)
            {
                gameBoard[i][j].SetTexture();
                sprites.push_back(gameBoard[i][j].GetSprite());
            }
        }
        int i = 0;
        for(vector<sf::Sprite>::iterator it = sprites.begin(); it != sprites.end(); ++it)
        {

            //qDebug() << "" << i << " sprite position x: " << (*it).getPosition().x << " y: " << (*it).getPosition().y << endl;
            Window.draw(*it);
            i++;
        }

        Window.display();
    }
    return 1;
}

QString MiniGameScreen::ReadFile(QString filePath)
{
    QResource gameRsrc(filePath);
    QFile gameFile(gameRsrc.absoluteFilePath());
    int lineNum = 0;
    gameFile.open(QIODevice::ReadOnly);
    QTextStream in(&gameFile);
    QString result;
    while(!in.atEnd())
    {
        result.append(in.readLine()).append(" ");
    }
    return result;
}

GameBoard MiniGameScreen::GetRowAndCol(QString fileName)
{

    GameBoard gb;
    QStringList fileList = fileName.split("/");
    QString realFileName = fileList.at(fileList.size() - 1);
    gb.rowNum = realFileName.at(0).toLatin1() - 48;
    gb.colNum = realFileName.at(2).toLatin1() - 48;
    return gb;
}

