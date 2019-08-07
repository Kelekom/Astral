#pragma once
#include<SFML/Graphics.hpp>
#include"AnimatedSprite.hpp"

class Player
{
public:
    Player();
    virtual ~Player();
    void Update(float elapsedSec);
    void Draw(sf::RenderWindow* pWindow);

private:
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;
    Animation* currentAnimation = &walkingAnimationDown;
    AnimatedSprite animatedSprite { sf::seconds(0.2), true, false };
};
