#include "player.h"

Player::Player(QObject *parent) : QObject(parent)
{
    QResource ghost(":/images/ghosty.png"); // player
    GhostTexture.loadFromMemory(ghost.data(), ghost.size());

    QResource box(":/images/box.png"); //player
    BoxTexture.loadFromMemory(box.data(), box.size()); //player

    CreateAnimations();
}

void Player::CreateBody(b2World &World, int MouseX, int MouseY)
{
    // grab the coordinates for the player from the bgm
    b2BodyDef BodyDef;
    BodyDef.position = b2Vec2(MouseX/SCALE, MouseY/SCALE);
    BodyDef.type = b2_dynamicBody;
    ghostBody = World.CreateBody(&BodyDef);
    ghostBody->SetGravityScale(0.f);
    ghostBody->SetUserData((void*)111);

    b2PolygonShape Shape;
    Shape.SetAsBox((32.f/2)/SCALE, (32.f/2)/SCALE);
    b2FixtureDef FixtureDef;
    //b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
//    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    ghostBody->CreateFixture(&FixtureDef);

}

void Player::ReplaceBody(b2World &World, int MouseX, int MouseY)
{
    //delete ghostBody;
    CreateBody(World, MouseX, MouseY);
}

void Player::CreateAnimations()
{
    walkingAnimationDown.setSpriteSheet(GhostTexture);
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
    walkingAnimationDown.addFrame(sf::IntRect( 0, 0, 32, 32));

    walkingAnimationLeft.setSpriteSheet(GhostTexture);
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
    walkingAnimationLeft.addFrame(sf::IntRect( 0, 32, 32, 32));

    walkingAnimationRight.setSpriteSheet(GhostTexture);
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
    walkingAnimationRight.addFrame(sf::IntRect( 0, 64, 32, 32));

    walkingAnimationUp.setSpriteSheet(GhostTexture);
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
    walkingAnimationUp.addFrame(sf::IntRect( 0, 96, 32, 32));

    currentAnimation = &walkingAnimationLeft;
    AnimatedSprite test(sf::seconds(0.2), true, false);
    animatedSprite = test;
    animatedSprite.setOrigin(16.f, 16.f);
    sf::Vector2i screenDimensions(800,600);
    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2));
}

void Player::SetAnimation(AnimationState state)
{
    switch(state)
    {
        case A_DOWN:
            currentAnimation = &walkingAnimationDown;
            break;
        case A_UP:
            currentAnimation = &walkingAnimationUp;
            break;
        case A_LEFT:
            currentAnimation = &walkingAnimationLeft;
            break;
        case A_RIGHT:
            currentAnimation = &walkingAnimationRight;
            break;
        case A_IDLE:
            animatedSprite.stop();
            break;
    }
}

void Player::Move(sf::Vector2f movement, float frameTime)
{
//    qDebug() << "ghost position " << ghostBody->GetPosition().x << " " << ghostBody->GetPosition().y << endl;
    b2Vec2 vec;
    vec.x = movement.x  * frameTime  * 2;
    vec.y = movement.y * frameTime * 2;
    ghostBody->SetLinearVelocity(vec);

    animatedSprite.setPosition(ghostBody->GetPosition().x * SCALE, ghostBody->GetPosition().y * SCALE);
    animatedSprite.play(*currentAnimation);
    animatedSprite.move(movement * frameTime);
}

void Player::UpdateAnimation(sf::Time frameTime)
{
    animatedSprite.update(frameTime);
}

void Player::SetSprite()
{
    Sprite.setOrigin(16.f, 16.f);
    Sprite.setTexture(BoxTexture);
    Sprite.setPosition(ghostBody->GetPosition().x * SCALE, ghostBody->GetPosition().y * SCALE);
}

AnimatedSprite Player::GetAnimatedSprite()
{
    return animatedSprite;
}

sf::Sprite Player::GetSprite()
{
    return Sprite;
}

float Player::GetPlayerSpeed()
{
    return speed;
}
