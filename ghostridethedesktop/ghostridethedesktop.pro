#-------------------------------------------------
#
# Project created by QtCreator 2017-11-27T12:07:13
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += std=c++11
TARGET = GhostRideTheDesktop
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11
QMAKE_RESOURCE_FLAGS += -compress 0
DEFINES += SFML_STATIC
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:!macx: LIBS+=-L$$PWD/../SFML-2.3.2/lib

unix:!macx:{
        LIBS += $$PWD/../SFML-2.3.2/lib/libsfml-audio-s.a\
        $$PWD/../SFML-2.3.2/lib/libsfml-window-s.a\
        $$PWD/../SFML-2.3.2/lib/libsfml-graphics-s.a\
        $$PWD/../SFML-2.3.2/lib/libsfml-network-s.a\
        $$PWD/../SFML-2.3.2/lib/libsfml-system-s.a\
        -lX11\
        -lxcb\
        -ljpeg\
        -lGL\
        -lxcb-randr\
        -lX11-xcb\
        -lfreetype\
        -lxcb-shm\
        $$PWD/../libxcb-image.a\
        $$PWD/../libxcb-util.a\
        $$PWD/../libudev.a
}

INCLUDEPATH += ../Box2D-master/Box2D \


unix:!macx: LIBS += -IQt5Concurrent

INCLUDEPATH+= ../SFML-2.3.2/include

RESOURCES += \
        resources.qrc
unix:!macx:{
    SOURCES += \
            main.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2BroadPhase.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2CollideCircle.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2CollideEdge.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2CollidePolygon.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2Collision.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2Distance.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2DynamicTree.cpp \
        ../Box2D-master/Box2D/Box2D/Collision/b2TimeOfImpact.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2BlockAllocator.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2Draw.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2Math.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2Settings.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2StackAllocator.cpp \
        ../Box2D-master/Box2D/Box2D/Common/b2Timer.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2Body.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2ContactManager.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2Fixture.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2Island.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2World.cpp \
        ../Box2D-master/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp \
        ../Box2D-master/Box2D/Box2D/Rope/b2Rope.cpp \
        paintsfmltexturewindow.cpp \
        qsfmlcanvas.cpp \
        AnimatedSprite.cpp \
        Animation.cpp \
        contactlistener.cpp \
        SFMLDebugDraw.cpp

    HEADERS += \
        paintsfmltexturewindow.h \
        qsfmlcanvas.h \
        contactlistener.h \
        SFMLDebugDraw.h
}

macx:{
    SOURCES += \
        main.cpp \
        paintsfmltexturewindow.cpp \
        AnimatedSprite.cpp \
        Animation.cpp \
        contactlistener.cpp \
        SFMLDebugDraw.cpp

    HEADERS += \
        paintsfmltexturewindow.h \
        contactlistener.h \
        SFMLDebugDraw.h
}

FORMS += \
        paintsfmltexturewindow.ui

unix:!macx: LIBS += -L$$PWD/../SFML-2.3.2/lib/ -lsfml-audio-s -lsfml-window-s -lsfml-graphics-s -lsfml-network-s -lsfml-system-s

INCLUDEPATH += $$PWD/../SFML-2.3.2/include
DEPENDPATH += $$PWD/../SFML-2.3.2/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../SFML-2.3.2/lib/libsfml-audio-s.a \
                               $$PWD/../SFML-2.3.2/lib/libsfml-graphics-s.a \
                                $$PWD/../SFML-2.3.2/lib/libsfml-network-s.a \
                                $$PWD/../SFML-2.3.2/lib/libsfml-system-s.a \
                                $$PWD/../SFML-2.3.2/lib/libsfml-window-s.a



macx: LIBS += -L$$PWD/../MAC/sfml/lib/ -lsfml-audio.2.4.2 -lsfml-graphics.2.4.2 -lsfml-window.2.4.2 -lsfml-network.2.4.2 -lsfml-system.2.4.2
macx: LIBS += -L$$PWD/../MAC/sfml/Frameworks/
macx: LIBS += -L$$PWD/../MAC/sfml/extlibs/

INCLUDEPATH += $$PWD/../MAC/sfml/include
DEPENDPATH += $$PWD/../MAC/sfml/include

macx: LIBS += -L$$PWD/../MAC/ -lBox2D

INCLUDEPATH += $$PWD/../MAC/Box2D
DEPENDPATH += $$PWD/../MAC/Box2D

macx: PRE_TARGETDEPS += $$PWD/../MAC/libBox2D.a

macx:{
    QMAKE_MAC_SDK = 10.13
}

HEADERS += \
    player.h \
    backgroundmanager.h \
    titlescreen.h \
    screen.h \
    worldscreen.h \
    minigamescreen.h \
    tile.h \
    fantile.h \
    ramtile.h \
    gputile.h \
    cputile.h \
    winscreen.h \
    infoscreen.h

SOURCES += \
    player.cpp \
    backgroundmanager.cpp \
    titlescreen.cpp \
    worldscreen.cpp \
    minigamescreen.cpp \
    fantile.cpp \
    screen.cpp \
    tile.cpp \
    ramtile.cpp \
    gputile.cpp \
    cputile.cpp \
    winscreen.cpp \
    infoscreen.cpp
