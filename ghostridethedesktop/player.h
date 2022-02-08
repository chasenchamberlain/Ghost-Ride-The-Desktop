#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "SFML/Graphics/AnimatedSprite.hpp"
#include <QResource>
#include <SFML/System.hpp>
#include <QDebug>

enum AnimationState {A_DOWN, A_UP, A_LEFT, A_RIGHT, A_IDLE};



class Player : public QObject
{
    Q_OBJECT
private:
    const float SCALE = 32.f;
    float speed = 200.f;

    b2Body* ghostBody;
    Animation* currentAnimation;
    AnimatedSprite animatedSprite;

    Animation walkingAnimationUp;
    Animation walkingAnimationRight;
    Animation walkingAnimationLeft;
    Animation walkingAnimationDown;

    sf::Texture BoxTexture;
    sf::Texture GhostTexture;

    sf::Sprite Sprite;

public:
    explicit Player(QObject *parent = nullptr);


    void CreateBody(b2World &World, int MouseX, int MouseY);
    void ReplaceBody(b2World &World, int MouseX, int MouseY);
    void CreateAnimations();
    void SetAnimation(AnimationState);
    void Move(sf::Vector2f movement, float frameTime);
    void UpdateAnimation(sf::Time);
    void SetSprite();
    AnimatedSprite GetAnimatedSprite();
    sf::Sprite GetSprite();
    float GetPlayerSpeed();

signals:

public slots:
};

#endif // PLAYER_H
