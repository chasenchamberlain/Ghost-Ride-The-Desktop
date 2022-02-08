#include "backgroundmanager.h"

BackgroundManager::BackgroundManager(QObject *parent) : QObject(parent)
{
    for(int i = 0; i < 6; i++)
    {
        clearedGames[i] = false;
    }
    QResource background(":/images/backgroundProto.png");
    BackgroundTexture.loadFromMemory(background.data(), background.size());

    QResource dave(":/images/dave.png");
    DaveTexture.loadFromMemory(dave.data(), dave.size());

    QResource pwr(":/images/powerSupply.png");
    PWRTexture.loadFromMemory(pwr.data(), pwr.size());

    QResource fan(":/images/CoolingSystem.png");
    FANTexture.loadFromMemory(fan.data(), fan.size());

    QResource cpu(":/images/CPU.png");
    CPUTexture.loadFromMemory(cpu.data(), cpu.size());

    QResource gpu(":/images/GPU.png");
    GPUTexture.loadFromMemory(gpu.data(), gpu.size());

    QResource ram(":/images/RAM.png");
    RAMTexture.loadFromMemory(ram.data(), ram.size());

    QResource hap(":/sounds/happytheme.ogg");
    bufferHappy.loadFromMemory(hap.data(), hap.size());

    QResource spook(":/sounds/spookytheme.ogg");
    bufferSpooky.loadFromMemory(spook.data(), spook.size());

    QResource daveSong(":/sounds/dave.ogg");
    bufferDave.loadFromMemory(daveSong.data(), daveSong.size());

    soundHappy.setBuffer(bufferHappy);
    soundHappy.setLoop(true);
    soundSpooky.setBuffer(bufferSpooky);
    soundSpooky.setLoop(true);
    soundDave.setBuffer(bufferDave);
    soundDave.setLoop(true);

    MapRooms();
    SetUpDaveAnimations();
    testCoords = rooms[currentRow][currentCol].playerCoords;
}

int BackgroundManager::GetRoomRow()
{
    return currentRow;
}

int BackgroundManager::GetRoomCol()
{
    return currentCol;
}

bool BackgroundManager::IsWelcome()
{
    return welcomeScreen;
}

void BackgroundManager::SetIsWelcome(bool flag)
{
    welcomeScreen = flag;
}

void BackgroundManager::CreateRoom(b2World& World)
{
    qDebug() << "The current room is = " <<  currentRow << "," << currentCol << endl;
    Room r = rooms[currentRow][currentCol];
    // Dave's room
    if(currentRow == 0 && currentCol == 0)
    {
        soundSpooky.pause();
        soundHappy.pause();
        soundDave.play();
        //play his music
        daveFight = true;
        CreateStub(715.f, 545.f, 110.f, 38.f, World);
        CreateStub(710.f, 505.f, 115.f, 30.f, World);
    }
    else if(currentRow == 0 && currentCol == 1)
    {
        bool roomsCleared = true;
        for(int i = 0; i < 5; i++)
        {
            if(!clearedGames[i])
            {
                roomsCleared = false;
            }
        }
        if(!roomsCleared)
        {
            CreateWall(World, WEST);
        }
        CreateStub(175.f, 79.f, 32.f, 58.f, World);
        CreateStub(323.f, 79.f, 103.f, 58.f, World);
        CreateStub(180.f, 525.f, 97.f, 58.f, World);
    }
    else if(currentRow == 0 && currentCol == 2)
    {
        CreateStub(350.f, 99.f, 320.f, 128.f, World);
    }
    else if(currentRow == 1 && currentCol == 0)
    {
        CreateStub(492.f, 115.f, 130.f, 58.f, World);
    }
    else if(currentRow == 1 && currentCol == 1)
    {
        CreateStub(288.f, 99.f, 64.f, 128.f, World);
        CreateStub(510.f, 99.f, 64.f, 128.f, World);
        CreateStub(410.f, 520.f, 388.f, 58.f, World);
    }
    else if(currentRow == 1 && currentCol == 2)
    {
        CreateStub(98.f, 535.f, 97.f, 58.f, World);
        CreateStub(700.f, 535.f, 110.f, 38.f, World);
    }
    else if(currentRow == 2 && currentCol == 0)
    {
        CreateStub(415.f, 512.f, 388.f, 58.f, World);
    }
    else if(currentRow == 2 && currentCol == 1)
    {
        CreateStub(84.f, 58.f, 70.f, 30.f, World);
        CreateStub(415.f, 99.f, 128.f, 128.f, World);
    }
    else if(currentRow == 2 && currentCol == 2)
    {
        CreateStub(235.f, 69.f, 382.f, 58.f, World);
    }

    if(currentRow == 2)
    {
        if((clearedGames[0] && clearedGames[1]) && soundHappy.getStatus()!=sf::Sound::Playing)
        {
            soundSpooky.pause();
            soundHappy.play();
        }
        else
        {
            if(soundSpooky.getStatus()!=sf::Sound::Playing && !(clearedGames[0] && clearedGames[1]))
            {
                soundHappy.pause();
                soundSpooky.play();
            }
        }
    }
    if(currentRow == 1)
    {
        if((clearedGames[2] && clearedGames[3]) && soundHappy.getStatus()!=sf::Sound::Playing)
        {
            soundSpooky.pause();
            soundHappy.play();
        }
        else
        {
            if(soundSpooky.getStatus()!=sf::Sound::Playing && !(clearedGames[2] && clearedGames[3]))
            {
                soundHappy.pause();
                soundSpooky.play();
            }
        }
    }
    if(currentRow == 0)
    {
        if(daveFight && currentCol == 0)
        {
            soundSpooky.pause();
            soundHappy.pause();
            soundDave.play();
        }
        else if(clearedGames[4] && soundHappy.getStatus()!=sf::Sound::Playing)
        {
            soundSpooky.pause();
            soundDave.pause();
            soundHappy.play();
        }
        else
        {
            if(soundSpooky.getStatus()!=sf::Sound::Playing && !(clearedGames[4]))
            {
                soundHappy.pause();
                soundDave.pause();
                soundSpooky.play();
            }
        }
    }
    for(vector<RoomEntity>::iterator it = r.walls.begin(); it != r.walls.end(); ++it)
    {
        CreateWall(World, *it);
    }
    for(vector<RoomEntity>::iterator it = r.sensors.begin(); it != r.sensors.end(); ++it)
    {
        CreateSensor(World, *it);
    }
}

void BackgroundManager::CreateWall(b2World& World, RoomEntity entity)
{
    float X, Y = 0;
    float shapeX, shapeY = 0;
    switch(entity)
    {
    case NORTH:
        X = 400.f;
        Y = 16.f;
        shapeX = 800.f;
        shapeY = 32.f;
        break;
    case EAST:
        X = 784.f;
        Y = 300.f;
        shapeX = 32.f;
        shapeY = 800.f;
        break;
    case SOUTH:
        X = 400.f;
        Y = 584.f;
        shapeX = 800.f;
        shapeY = 32.f;
        break;
    case WEST:
        X = 16.f;
        Y = 300.f;
        shapeX = 32.f;
        shapeY = 800.f;
        break;
    default:
        return;
    }
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((shapeX/2)/SCALE, (shapeY/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    FixtureDef.userData = (void*)3;
    Body->CreateFixture(&FixtureDef);
}

void BackgroundManager::CreateStub(float X, float Y, float shapeX, float shapeY, b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((shapeX/2)/SCALE, (shapeY/2)/SCALE);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    FixtureDef.userData = (void*)3;
    Body->CreateFixture(&FixtureDef);
}

void BackgroundManager::CreateSensor(b2World& World, RoomEntity entity)
{
    float X, Y = 0;
    float shapeX, shapeY = 0;

    UserData *data = new UserData;
    data->roomRow = currentRow;
    data->roomCol = currentCol;

    qDebug() << entity << endl;

    switch(entity)
    {
    case NORTH:
        X = 400.f;
        Y = -16.f;
        shapeX = 800.f;
        shapeY = 32.f;
        data->entity = NORTH;
        CreateStub(45.f, 16.f, 200.f, 32.f, World);
        CreateStub(755.f, 16.f, 200.f, 32.f, World);
        break;
    case EAST:
        X = 816.f;
        Y = 300.f;
        shapeX = 32.f;
        shapeY = 800.f;
        data->entity = EAST;
        CreateStub(784.f, 27.f, 32.f, 200.f, World);
        CreateStub(784.f, 578.f, 32.f, 200.f, World);
        break;
    case SOUTH:
        X = 400.f;
        Y = 616.f;
        shapeX = 800.f;
        shapeY = 32.f;
        data->entity = SOUTH;
        CreateStub(45.f, 584.f, 200.f, 32.f, World);
        CreateStub(755.f, 584.f, 200.f, 32.f, World);
        break;
    case WEST:
        X = -16.f;
        Y = 300.f;
        shapeX = 32.f;
        shapeY = 800.f;
        data->entity = WEST;
        CreateStub(16.f, 27.f, 32.f, 200.f, World);
        CreateStub(16.f, 578.f, 32.f, 200.f, World);
        break;
    case INFO1:
        X = 432.f;
        Y = 332.f;
        shapeX = 64.f;
        shapeY = 128.f;
        data->entity = INFO1;
        break;
    case INFO2:
        X = 382.f;
        Y = 96.f;
        shapeX = 64.f;
        shapeY = 128.f;
        data->entity = INFO2;
        break;
    case INFO3:
        X = 736.f;
        Y = 200.f;
        shapeX = 64.f;
        shapeY = 128.f;
        data->entity = INFO3;
        break;
    case PWR:
    {
        X = 400.f;
        Y = 520.f;
        shapeX = 252.f;
        shapeY = 96.f;
        data->entity = PWR;

        currentAnimation = PWRAnimation;

        AnimatedSprite test(sf::seconds(0.2), true, false);
        //test.scale(2.3,2.3);
        currentAnimatedSprite = test;
        currentAnimatedSprite.setOrigin(126.f, 48.f);
        sf::Vector2i screenDimensions(800,600);
        currentAnimatedSprite.setPosition(X, Y);

    }
        break;
    case FAN:
    {
        X = 96.f;
        Y = 300.f;
        shapeX = 128.f;
        shapeY = 128.f;
        data->entity = FAN;

        currentAnimation = FANAnimation;

        AnimatedSprite test(sf::seconds(0.2), true, false);
        //test.scale(2.3,2.3);
        currentAnimatedSprite = test;
        currentAnimatedSprite.setOrigin(64.f, 64.f);
        sf::Vector2i screenDimensions(800,600);
        currentAnimatedSprite.setPosition(X, Y);
    }
        break;
    case CPU:
    {
        X = 400.f;
        Y = 96.f;
        shapeX = 128.f;
        shapeY = 128.f;
        data->entity = CPU;

        currentAnimation = CPUAnimation;

        AnimatedSprite test(sf::seconds(0.1), true, false);
        //test.scale(2.3,2.3);
        currentAnimatedSprite = test;
        currentAnimatedSprite.setOrigin(64.f, 64.f);
        sf::Vector2i screenDimensions(800,600);
        currentAnimatedSprite.setPosition(X, Y);
    }
        break;
    case GPU:
    {
        X = 400.f;
        Y = 498.f;
        shapeX = 298.f;
        shapeY = 140.f;
        data->entity = GPU;

        currentAnimation = GPUAnimation;

        AnimatedSprite test(sf::seconds(0.2), true, false);
        //test.scale(2.3,2.3);
        currentAnimatedSprite = test;
        //298, 140
        currentAnimatedSprite.setOrigin(149.f, 70.f);
        sf::Vector2i screenDimensions(800,600);
        currentAnimatedSprite.setPosition(X, Y);
    }
        break;
    case RAM:
    {
        X = 400.f;
        Y = 520.f;
        shapeX = 196.f;
        shapeY = 96.f;
        data->entity = RAM;

        currentAnimation = RAMAnimation;
        //196,96
        AnimatedSprite test(sf::seconds(0.1), true, false);
        currentAnimatedSprite = test;
        currentAnimatedSprite.setOrigin(98.f, 48.f);
        sf::Vector2i screenDimensions(800,600);
        currentAnimatedSprite.setPosition(X, Y);
    }
        break;
    case DAVE:
    {
        data->entity = DAVE;
        currentAnimation = DaveAnimation;

        AnimatedSprite test(sf::seconds(0.2), true, false);
        test.scale(2.f,2.f);
        currentAnimatedSprite = test;
        currentAnimatedSprite.setPosition(200, 160);

        b2BodyDef BodyDef;
        BodyDef.position = b2Vec2((200 + 4*32 - 20)/SCALE, (160 + 4*32 + 20)/SCALE);
        BodyDef.type = b2_staticBody;
        b2Body* Body = World.CreateBody(&BodyDef);

        b2CircleShape circleShape;
        circleShape.m_p.Set(0, 0); //position, relative to body position
        circleShape.m_radius = 4.25; //radius

        b2FixtureDef FixtureDef;
        FixtureDef.density = 0.f;
        FixtureDef.shape = &circleShape;
        FixtureDef.isSensor = true;
        FixtureDef.userData = (void*)data;
        Body->CreateFixture(&FixtureDef);
        DaveBody = Body;

          return;
    }
        break;
    case WIN:
        X = 111.f;
        Y = 480.f;
        shapeX = 128.f;
        shapeY = 128.f;
        data->entity = WIN;
        break;
    case MAC:
        X = 111.f;
        Y = 130.f;
        shapeX = 128.f;
        shapeY = 128.f;
        data->entity = MAC;
        break;
    case LIN:
        X = 111.f;
        Y = 303.f;
        shapeX = 128.f;
        shapeY = 128.f;
        data->entity = LIN;
        break;
    default:
        return;
    }

    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(X/SCALE, Y/SCALE);
    BodyDef.type = b2_staticBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    b2PolygonShape Shape;
    Shape.SetAsBox((shapeX/2)/SCALE, (shapeY/2)/SCALE);

    b2FixtureDef FixtureDef;
    FixtureDef.density = 0.f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = true;
    FixtureDef.userData = (void*)data;
    Body->CreateFixture(&FixtureDef);
}

void BackgroundManager::SetSprites()
{
    sprites.clear();
    sf::Sprite Background;
    Background.setTexture(BackgroundTexture);
    Background.setOrigin(800, 0);
    sf::Vector2f backVec;
    backVec.x = currentCol * 800;
    backVec.y = currentRow * 600;
    Background.setOrigin(backVec);
    sprites.push_back(Background);
}

vector<sf::Sprite> BackgroundManager::GetSprites()
{
    return sprites;
}

void BackgroundManager::IncrementCounter()
{
    lostCounter++;
}

int BackgroundManager::GetLostCounter()
{
    return lostCounter;
}

b2Vec2 BackgroundManager::GetPlayerCoords()
{
    return testCoords;
}

b2Vec2 BackgroundManager::GetOriginalPlayerCoords()
{
    return rooms[currentRow][currentCol].playerCoords;
}

void BackgroundManager::moveDave(float Y)
{
    float DaveY = DaveBody->GetPosition().y *32;
    if((DaveY >= 50||moveDown) && (DaveY <= 550||!moveDown))
    {
        if(moveDown)
        {
          DaveBody->SetTransform(DaveBody->GetPosition() + b2Vec2(0, Y), 0);
        }
        if(!moveDown)
        {
            DaveBody->SetTransform(DaveBody->GetPosition() + b2Vec2(0, -Y), 0);
        }
    }
    else
    {
        if(moveDown)
        {
            moveDown = false;
        }
        else
        {
            moveDown = true;
        }
    }
    currentAnimatedSprite.setOrigin(50, 80);
    currentAnimatedSprite.setPosition(DaveBody->GetPosition().x*32,DaveBody->GetPosition().y*32);
}

void BackgroundManager::CreateBullet(b2World& World)
{
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(DaveBody->GetPosition().x, DaveBody->GetPosition().y);
    BodyDef.type = b2_dynamicBody;
    b2Body* Body = World.CreateBody(&BodyDef);

    int randx = rand()%3;
    if(randx==0)
    {
        Body->SetUserData((void*)765);
    }
    else if(randx==1)
    {
        Body->SetUserData((void*)766);
    }
    else if(randx==2)
    {
        Body->SetUserData((void*)767);
    }

    b2PolygonShape Shape;
    Shape.SetAsBox((16.f/2)/32, (16.f/2)/32);
    b2FixtureDef FixtureDef;
    FixtureDef.density = 10.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    FixtureDef.isSensor = true;
    Body->CreateFixture(&FixtureDef);
    Body->SetGravityScale(0.f);

    int neg = rand()%2;
    if(neg==0)
    {
        Body->SetLinearVelocity(b2Vec2(10,10));
    }
    else if(neg == 1)
    {
        Body->SetLinearVelocity(b2Vec2(10,(-1)*10));
    }
}

void BackgroundManager::SetPlayerCoords(b2Vec2 coords)
{
    testCoords = coords;
}

void BackgroundManager::SetRoom(b2Vec2 coords)
{
    currentRow = coords.y / 600;
    currentCol = coords.x / 800;
}

void BackgroundManager::SetMiniGameCleared(RoomEntity game)
{
    clearedGames[game - 7] = true;
}

void BackgroundManager::MapRooms()
{
    Room r00;
    r00.walls.push_back(NORTH);
    r00.walls.push_back(WEST);
    r00.walls.push_back(SOUTH);
    r00.walls.push_back(EAST);
    //r00.sensors.push_back(EAST);
    r00.sensors.push_back(WIN);
    r00.sensors.push_back(MAC);
    r00.sensors.push_back(LIN);
    r00.sensors.push_back(DAVE);
    r00.playerCoords.x = 730.f;
    r00.playerCoords.y = 300.f;
    DaveAnimation.setSpriteSheet(DaveTexture);
    DaveAnimation.addFrame(sf::IntRect(0, 0, 104, 160));
    DaveAnimation.addFrame(sf::IntRect(104, 0, 104, 160));
    rooms[0][0] = r00;

    Room r01;
    r01.walls.push_back(NORTH);
    r01.walls.push_back(SOUTH);
    r01.sensors.push_back(WEST);
    r01.sensors.push_back(EAST);
    r01.sensors.push_back(RAM);
    r01.playerCoords.x = 730.f;
    r01.playerCoords.y = 300.f;
    RAMAnimation.setSpriteSheet(RAMTexture);
    RAMAnimation.addFrame(sf::IntRect(0, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(196, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(392, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(588, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(784, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(980, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(1176, 0, 196, 96));
    RAMAnimation.addFrame(sf::IntRect(1372, 0, 196, 96));
    rooms[0][1] = r01;

    Room r02;
    r02.walls.push_back(NORTH);
    r02.walls.push_back(EAST);
    r02.sensors.push_back(SOUTH);
    r02.sensors.push_back(WEST);
    r02.sensors.push_back(INFO3);
    r02.playerCoords.x = 400.f;
    r02.playerCoords.y = 530.f;
    rooms[0][2] = r02;

    Room r12;
    r12.walls.push_back(EAST);
    r12.walls.push_back(SOUTH);
    r12.sensors.push_back(WEST);
    r12.sensors.push_back(NORTH);
    r12.sensors.push_back(GPU);
    r12.playerCoords.x = 70.f;
    r12.playerCoords.y = 300.f;
    GPUAnimation.setSpriteSheet(GPUTexture);
    GPUAnimation.addFrame(sf::IntRect(0, 0, 298, 140));
    GPUAnimation.addFrame(sf::IntRect(298, 0, 298, 140));
    GPUAnimation.addFrame(sf::IntRect(596, 0, 298, 140));
    GPUAnimation.addFrame(sf::IntRect(894, 0, 298, 140));
    rooms[1][2] = r12;

    Room r11;
    r11.walls.push_back(NORTH);
    r11.sensors.push_back(WEST);
    r11.walls.push_back(SOUTH);
    r11.sensors.push_back(EAST);
    r11.sensors.push_back(CPU);
    r11.playerCoords.x = 70.f;
    r11.playerCoords.y = 300.f;
    CPUAnimation.setSpriteSheet(CPUTexture);
    CPUAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(512, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(640, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(768, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(896, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(1024, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(1152, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(1280, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(1408, 0, 128, 128));
    CPUAnimation.addFrame(sf::IntRect(1536, 0, 128, 128));
    rooms[1][1] = r11;

    Room r10;
    r10.walls.push_back(NORTH);
    r10.walls.push_back(WEST);
    r10.sensors.push_back(SOUTH);
    r10.sensors.push_back(EAST);
    r10.sensors.push_back(INFO2);
    r10.playerCoords.x = 400.f;
    r10.playerCoords.y = 530.f;
    rooms[1][0] = r10;

    Room r20;
    r20.sensors.push_back(NORTH);
    r20.walls.push_back(WEST);
    r20.walls.push_back(SOUTH);
    r20.sensors.push_back(EAST);
    r20.sensors.push_back(FAN);
    r20.playerCoords.x = 730.f;
    r20.playerCoords.y = 300.f;
    FANAnimation.setSpriteSheet(FANTexture);
    FANAnimation.addFrame(sf::IntRect(0, 0, 128, 128));
    FANAnimation.addFrame(sf::IntRect(128, 0, 128, 128));
    FANAnimation.addFrame(sf::IntRect(256, 0, 128, 128));
    FANAnimation.addFrame(sf::IntRect(384, 0, 128, 128));
    rooms[2][0] = r20;

    Room r21;
    r21.walls.push_back(NORTH);
    r21.sensors.push_back(WEST);
    r21.walls.push_back(SOUTH);
    r21.sensors.push_back(EAST);
    r21.sensors.push_back(PWR);
    r21.playerCoords.x = 730.f;
    r21.playerCoords.y = 300.f;
    PWRAnimation.setSpriteSheet(PWRTexture);
    PWRAnimation.addFrame(sf::IntRect(0, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(252, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(504, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(756, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(1008, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(1260, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(1512, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(1764, 0, 252, 96));
    PWRAnimation.addFrame(sf::IntRect(2016, 0, 252, 96));
    rooms[2][1] = r21;

    Room r22;
    r22.walls.push_back(NORTH);
    r22.walls.push_back(EAST);
    r22.walls.push_back(SOUTH);
    r22.sensors.push_back(WEST);
    r22.sensors.push_back(INFO1);
    r22.playerCoords.x = 730.f;
    r22.playerCoords.y = 300.f;
    rooms[2][2] = r22;
}

void BackgroundManager::SetUpDaveAnimations()
{
    DaveAnimation.setSpriteSheet(DaveTexture);
    DaveAnimation.addFrame(sf::IntRect(0, 0, 104, 160));
    DaveAnimation.addFrame(sf::IntRect(104, 0, 104, 160));
    currentAnimation = DaveAnimation;

    AnimatedSprite test(sf::seconds(0.5), true, false);
    test.scale(2.3,2.3);
    currentAnimatedSprite = test;
    currentAnimatedSprite.setOrigin(16.f, 16.f);
    sf::Vector2i screenDimensions(800,600);
    currentAnimatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
}

void BackgroundManager::UpdateCurrentAnimation(sf::Time frameTime)
{
    currentAnimatedSprite.update(frameTime);
}

void BackgroundManager::PlayCurrentAnimation()
{
    currentAnimatedSprite.play(currentAnimation);
}

bool BackgroundManager::IsCurrentRoomComplete()
{
    if(currentCol == 1 && currentRow == 2)
    {
        return clearedGames[0];
    }
    else if(currentCol == 0 && currentRow == 2)
    {
        return clearedGames[1];
    }
    else if(currentCol == 1 && currentRow == 1)
    {
        return clearedGames[2];
    }
    else if(currentCol == 2 && currentRow == 1)
    {
        return clearedGames[3];
    }
    else if(currentCol == 1 && currentRow == 0)
    {
        return clearedGames[4];
    }
    else if(currentCol == 0 && currentRow == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
