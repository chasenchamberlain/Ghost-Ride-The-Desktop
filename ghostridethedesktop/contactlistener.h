#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <QObject>
#include <SFML/System.hpp>
#include <QDebug>
//#include <Box2D/Box2D.h>
#include <Box2D.h>

#include "backgroundmanager.h"

enum Transition {NONE, TOP, RIGHT, BOTTOM, LEFT};

class ContactListener: public b2ContactListener
{
private:
    int backX;
    int backY;
    int numOfContacts = 0;
    int miniGameScreen = 0;
    bool roomChange = false;
    Transition tranny = NONE;
    bool lostToDave = false;
    bool youWin = false;
    int lostCounter = 0;

public:
    //whether or not the player in the power supply game is grounded
    bool isGrounded;
    //current charge of the power supply game
    int charge;

    ContactListener();
    // Called when two fixtures begin to touch
    virtual void BeginContact(b2Contact* contact);

    // Called when two fixtures cease to touch
    virtual void EndContact(b2Contact* contact);

    b2Vec2 getCoord();
    Transition GetTransitionType();
    bool RoomChanged();
    void SetRoomChanged(bool flag);
    int MiniGameLaunched();
    bool DaveLost();
    void SetDaveLost(bool val);
    int GetLostCounter();
    bool EndGame();
};

#endif // CONTACTLISTENER_H
