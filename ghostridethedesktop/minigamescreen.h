#ifndef MINIGAMESCREEN_H
#define MINIGAMESCREEN_H

#include <QObject>
#include <QFile>
#include <screen.h>
#include <vector>
#include <QTextStream>
#include <QResource>
#include "tile.h"
#include "ramtile.h"
#include "fantile.h"
#include "gputile.h"
#include "cputile.h"
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <QLinkedList>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>


struct GameBoard
{
    int rowNum;
    int colNum;
};

class MiniGameScreen : public Screen
{
private:
    enum MiniGameID {MG_PWR, MG_FAN, MG_CPU, MG_GPU, MG_RAM};
    MiniGameID ID;
    bool isCleared;

    // Put your minigame methods here.
    int PowerSupplyGame(b2World& World, BackgroundManager& bgm);
    int CoolingGame(b2World& World, BackgroundManager& bgm);
    int CPUGame(b2World& World, BackgroundManager& bgm);
    int GPUGame(b2World& World, BackgroundManager& bgm);
    int RAMGame(b2World& World, BackgroundManager& bgm);

    QString ReadFile(QString filePath);
    string QuestionText(int questionNumber);
    vector<int> QuestionAnswers(int questionNumber);
    GameBoard GetRowAndCol(QString fileName);
    sf::RectangleShape DrawSelected(int tileNum);
    bool CheckFanSolution(int col, int row, int dir, FANTile GameBoard[6][6], sf::Vector2f cpu);

    void CreateTileBox(b2World &World, int x, int y, sf::Sprite &);
    void CreatePowerSupplyBody(float width, float height, float x, float y, bool isSensor, b2World& World);
    void CreatePowerSupplySparks(float width, float height, float x, float y, b2World& World);
public:
    MiniGameScreen();
    MiniGameScreen(RoomEntity ID);
    int Run (b2World& World, BackgroundManager& bgm);
};

#endif // MINIGAMESCREEN_H
