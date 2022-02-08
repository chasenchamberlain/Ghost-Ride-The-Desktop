#ifndef BACKGROUNDMANAGER_H
#define BACKGROUNDMANAGER_H

#include <QObject>
#include <vector>
//#include <Box2D/Box2D.h>
#include <Box2D.h>

#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/AnimatedSprite.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <QResource>
#include <QDebug>

using namespace std;

enum RoomEntity {NORTH, EAST, SOUTH, WEST, INFO1, INFO2, INFO3, PWR, FAN, CPU, GPU, RAM, DAVE, WIN, MAC, LIN};

class BackgroundManager : public QObject
{
    Q_OBJECT
private:


    struct Room
    {
         vector<RoomEntity> walls;
         vector<RoomEntity> sensors;
         b2Vec2 playerCoords;
    };

    const float SCALE = 32.f;
    static const int ROW = 3;
    static const int COLUMN = 3;

    /*
     * 0. PWR  3. GPU
     * 1. FAN  4. RAM
     * 2. CPU  5. DAVE
     */
    bool clearedGames[6];
    bool welcomeScreen = true;

    // FOR DEBUGGING, YOU CAN SET YOU CURRENT ROOM HERE
    int currentRow = 2;
    int currentCol = 2;

    b2Vec2 testCoords;
    b2Body* DaveBody;
    bool moveDown = true;
    int lostCounter = 0;


    Room rooms[ROW][COLUMN];

    vector<sf::Sprite> sprites;

    sf::Texture NorthTexture;
    sf::Texture SouthTexture;
    sf::Texture WestTexture;
    sf::Texture EastTexture;
    sf::Texture BackgroundTexture;
    sf::Texture DaveTexture;
    sf::Texture PWRTexture;
    sf::Texture FANTexture;
    sf::Texture CPUTexture;
    sf::Texture GPUTexture;
    sf::Texture RAMTexture;



    Animation DaveAnimation;
    Animation PWRAnimation;
    Animation FANAnimation;
    Animation CPUAnimation;
    Animation GPUAnimation;
    Animation RAMAnimation;

//    bool firstCleared;
//    bool secondCleared;
//    bool thirdCleared;
    bool daveFight;
    sf::SoundBuffer bufferHappy;
    sf::SoundBuffer bufferSpooky;
    sf::SoundBuffer bufferDave;
void CreateStub(float, float, float, float, b2World&);





public:
    struct UserData
    {
        int roomRow;
        int roomCol;
        RoomEntity entity;
    };

    Animation currentAnimation;
    AnimatedSprite currentAnimatedSprite;
    sf::Sound soundHappy;
    sf::Sound soundSpooky;
    sf::Sound soundDave;
    sf::Sound currentSong;
    bool gameWon = false;


    bool lostToDave = false;

    explicit BackgroundManager(QObject *parent = nullptr);

    void CreateRoom(b2World& World);
    void CreateWall(b2World& World, RoomEntity entity);
    void CreateSensor(b2World& World, RoomEntity entity);
    void SetSprites();
    vector<sf::Sprite> GetSprites();
    b2Vec2 GetPlayerCoords();
    void SetPlayerCoords(b2Vec2 coords);
    void SetRoom(b2Vec2 coords);
    void MapRooms();
    void SetUpDaveAnimations();
    void SetMiniGameCleared(RoomEntity game);
    void UpdateCurrentAnimation(sf::Time frameTime);
    void PlayCurrentAnimation();
    int GetRoomRow();
    int GetRoomCol();
    bool IsWelcome();
    void SetIsWelcome(bool);
    bool IsCurrentRoomComplete();
    void moveDave(float Y);
    void CreateBullet(b2World& World);
    b2Vec2 GetOriginalPlayerCoords();
    void IncrementCounter();
    int GetLostCounter();
signals:

public slots:
};

#endif // BACKGROUNDMANAGER_H
