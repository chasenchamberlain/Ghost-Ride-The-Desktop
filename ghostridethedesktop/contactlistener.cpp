#include "contactlistener.h"

ContactListener::ContactListener()
{
    backX = 1600;
    backY = 1200;
}

void ContactListener::BeginContact(b2Contact* contact)
{
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
    {
        //qDebug() << "----------------SENSOR!!--------------------------" << endl;
        BackgroundManager::UserData* room;
        if(contact->GetFixtureA()->IsSensor())
        {
            room = (BackgroundManager::UserData*)contact->GetFixtureA()->GetUserData();
        }
        else
        {
            room = (BackgroundManager::UserData*)contact->GetFixtureB()->GetUserData();
        }
        if(room == NULL)
        {
            void* userdata1 = (void*)0;
            void* userdata2 = (void*)0;
            userdata1 = contact->GetFixtureA()->GetBody()->GetUserData();
            userdata2 = contact->GetFixtureB()->GetBody()->GetUserData();
            if((userdata1 == (void*)54321 && userdata2 == (void*)4200)||(userdata1 == (void*)4200 && userdata2 == (void*)54321))
            {
               isGrounded = true;
            }
            if((userdata1 == (void*)420 && userdata2 == (void*)4200)||(userdata1 == (void*)4200 && userdata2 == (void*)420))
            {
                qDebug() << "----------------SPARK HIT GUY--------------------------" << endl;
                charge += 50;
            }
            if((userdata1 == (void*)765 && userdata2 == (void*)111)||(userdata1 == (void*)111 && userdata2 == (void*)765))
            {
                //qDebug() << "----------------BULLET HIT GUY--------------------------" << endl;
                backX = 800;
                backY = 0;
                roomChange = true;
                lostToDave = true;
                lostCounter++;
            }
            if((userdata1 == (void*)766 && userdata2 == (void*)111)||(userdata1 == (void*)111 && userdata2 == (void*)766))
            {
                //qDebug() << "----------------BULLET HIT GUY--------------------------" << endl;
                backX = 800;
                backY = 0;
                roomChange = true;
                lostToDave = true;
                lostCounter++;
            }
            if((userdata1 == (void*)767 && userdata2 == (void*)111)||(userdata1 == (void*)111 && userdata2 == (void*)767))
            {
                //qDebug() << "----------------BULLET HIT GUY--------------------------" << endl;
                backX = 800;
                backY = 0;
                roomChange = true;
                lostToDave = true;
                lostCounter++;
            }
        }
        else
        {
            switch(room->entity)
            {
            case NORTH:
                backX = room->roomCol * 800;
                backY = (room->roomRow - 1) * 600;
                roomChange = true;
                tranny = TOP;
                break;
            case EAST:
                backX = (room->roomCol + 1) * 800;
                backY = room->roomRow * 600;
                roomChange = true;
                tranny = RIGHT;
                break;
            case SOUTH:
                backX = room->roomCol * 800;
                backY = (room->roomRow + 1) * 600;
                roomChange = true;
                tranny = BOTTOM;
                break;
            case WEST:
                backX = (room->roomCol - 1) * 800;
                backY = room->roomRow * 600;
                roomChange = true;
                tranny = LEFT;
                break;
            case INFO1:
            case INFO2:
            case INFO3:
            case PWR:
            case FAN:
            case CPU:
            case GPU:
            case RAM:
                miniGameScreen = 8;
                break;
            case DAVE:
            {
                backX = 800;
                backY = 0;
                roomChange = true;
                lostToDave = true;
                lostCounter++;
                break;
            }
            case WIN:
            case MAC:
            case LIN:
                backX = 1600;
                backY = 1200;
                youWin = true;
                break;
            default:
                return;
            }
        }
    }
    else
    {
        //qDebug() << "----------------BEGIN COLLIDING!!--------------------------" << endl;
    }
}

void ContactListener::EndContact(b2Contact* contact)
{
    //qDebug() << "----------------END COLLIDING!!--------------------------" << endl;
    if(contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
    {
        BackgroundManager::UserData* room;
        if(contact->GetFixtureA()->IsSensor())
        {
            room = (BackgroundManager::UserData*)contact->GetFixtureA()->GetUserData();
        }
        else
        {
            room = (BackgroundManager::UserData*)contact->GetFixtureB()->GetUserData();
        }
        if(room != NULL && (room->entity == WIN || room->entity == MAC || room->entity == LIN))
        {
            youWin = false;
        }
        miniGameScreen = 0;
    }
}

b2Vec2 ContactListener::getCoord()
{
    return b2Vec2(backX, backY);
}

Transition ContactListener::GetTransitionType()
{
    return tranny;
}

bool ContactListener::RoomChanged()
{
    return roomChange;
}

void ContactListener::SetRoomChanged(bool flag)
{
    roomChange = flag;
}

int ContactListener::MiniGameLaunched()
{
    return miniGameScreen;
}

bool ContactListener::DaveLost()
{
    return lostToDave;
}

void ContactListener::SetDaveLost(bool val)
{
    lostToDave = val;
}

int ContactListener::GetLostCounter()
{
    return lostCounter;
}

bool ContactListener::EndGame()
{
    return youWin;
}
