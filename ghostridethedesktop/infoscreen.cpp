#include "infoscreen.h"

InfoScreen::InfoScreen()
{

}

int InfoScreen::Run (b2World& World, BackgroundManager& bgm)
{
    int nextScreen = GetNextScreen(bgm); // calculate next screen to go to.


    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "[ghost@UofU/terminal ~]$  " + selectedTitle + ".md", sf::Style::Close);
    Window.setFramerateLimit(30);
    Window.setMouseCursorVisible(false);

    QResource background(":images/titleScreenMockup.png");
    sf::Texture backgroundT;
    backgroundT.loadFromMemory(background.data(), background.size());
    sf::Sprite backgroundS;
    backgroundS.setTexture(backgroundT);

    // textShader
    sf::RectangleShape textShader(sf::Vector2f(650, 200));
    textShader.setOrigin(0,0);
    textShader.setPosition(80,200);
    textShader.setFillColor(sf::Color(0,0,0));

    // set and load text
    sf::Font font;
    QResource fontbruh(":/computer_pixel-7.ttf");
    font.loadFromMemory(fontbruh.data(), fontbruh.size());
    sf::Text timertext;
    timertext.setString(selectedText);
    timertext.setFont(font);
    timertext.setCharacterSize(46);
    timertext.setStyle(sf::Text::Regular);
    timertext.setFillColor(sf::Color::Green);
    timertext.setPosition(80, 60);

    sf::Text EnterToLeavetext;
    EnterToLeavetext.setString("(Press ENTER to leave)");
    EnterToLeavetext.setFont(font);
    EnterToLeavetext.setCharacterSize(18);
    EnterToLeavetext.setStyle(sf::Text::Regular);
    EnterToLeavetext.setFillColor(sf::Color::Green);
    EnterToLeavetext.setPosition(585, 515);


    isRunning = true;

    sf::Clock displayClock;
    sf::Clock clock;
    bool showText = false;
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
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Return)
            {
                Window.close();
                isRunning = false;
                return nextScreen;
            }
        }
        Window.draw(backgroundS);
        Window.draw(textShader);
        Window.draw(timertext);
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
        Window.display();
    }
}

int InfoScreen::GetNextScreen(BackgroundManager& bgm)
{
    int screen = -1;

    //handle the code for the welcome screen
    if(bgm.IsWelcome())
    {
        bgm.SetIsWelcome(false);
        return 1;
    }

    if(bgm.GetRoomRow() == 2 && bgm.GetRoomCol() == 2 && bgm.gameWon)
    {
        screen = 1;
        bgm.soundDave.stop();
        bgm.soundHappy.play();
        bgm.lostToDave = false;
        selectedText = "Congratulations! You have beaten \n404 Dave and have successfully built \nyour PC.\nThanks for playing Ghost Ride the \nDesktop!\n\nCREDITS: \nChasen Chamberlain, Daxton Wilson, \nJoshua Homer, Ryan Cantera, \nStephen Hogan";
        selectedTitle = "Conclusion";
    }
    else if(bgm.GetRoomRow() == 2 && bgm.GetRoomCol() == 2)
    {
        screen = 1;
        selectedText = infos[1];
        selectedTitle = titles[1];

    }
    else if(bgm.GetRoomRow() == 2 && bgm.GetRoomCol() == 1)
    {
        screen = 2;
        selectedText = infos[2];
        selectedTitle = titles[2];
    }
    else if(bgm.GetRoomRow() == 2 && bgm.GetRoomCol() == 0)
    {
        screen = 3;
        selectedText = infos[3];
        selectedTitle = titles[3];
    }
    else if(bgm.GetRoomRow() == 1 && bgm.GetRoomCol() == 2)
    {
        screen = 5;
        selectedText = infos[6];
        selectedTitle = titles[6];
    }
    else if(bgm.GetRoomRow() == 1 && bgm.GetRoomCol() == 1)
    {
        screen = 4;
        selectedText = infos[5];
        selectedTitle = titles[5];
    }
    else if(bgm.GetRoomRow() == 1 && bgm.GetRoomCol() == 0)
    {
        screen = 1;
        selectedText = infos[4];
        selectedTitle = titles[4];
    }
    else if(bgm.GetRoomRow() == 0 && bgm.GetRoomCol() == 2)
    {
        screen = 1;
        selectedText = infos[7];
        selectedTitle = titles[7];
    }
    else if(bgm.GetRoomRow() == 0 && bgm.GetRoomCol() == 1)
    {
        screen = 6;
        selectedText = infos[8];
        selectedTitle = titles[8];
    }
    return screen;
}

