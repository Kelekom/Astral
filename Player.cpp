#include"Player.hpp"
#include"AssetManager.hpp"
#include"InputManager.hpp"
#include"AnimatedSprite.hpp"

Player::Player()
{

    walkingAnimationDown.setSpriteSheet(*(AssetManager::getInstance()->requestTexture("celesWalking")));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 48));
    walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 48));
    walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 48));
    walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 48));

    walkingAnimationLeft.setSpriteSheet(*(AssetManager::getInstance()->requestTexture("celesWalking")));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 48, 32, 48));
    walkingAnimationLeft.addFrame(sf::IntRect(64, 48, 32, 48));
    walkingAnimationLeft.addFrame(sf::IntRect(32, 48, 32, 48));
    walkingAnimationLeft.addFrame(sf::IntRect(0, 48, 32, 48));

    walkingAnimationRight.setSpriteSheet(*(AssetManager::getInstance()->requestTexture("celesWalking")));
    walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 48));
    walkingAnimationRight.addFrame(sf::IntRect(64, 96, 32, 48));
    walkingAnimationRight.addFrame(sf::IntRect(32, 96, 32, 48));
    walkingAnimationRight.addFrame(sf::IntRect(0, 96, 32, 48));

    walkingAnimationUp.setSpriteSheet(*(AssetManager::getInstance()->requestTexture("celesWalking")));
    walkingAnimationUp.addFrame(sf::IntRect(32, 144, 32, 48));
    walkingAnimationUp.addFrame(sf::IntRect(64, 144, 32, 48));
    walkingAnimationUp.addFrame(sf::IntRect(32, 144, 32, 48));
    walkingAnimationUp.addFrame(sf::IntRect(0, 144, 32, 48));
}

Player::~Player()
{

}

void Player::Update(float elapsedSec)
{
    auto input = InputManager::getInstance();

    float speed = 80.0f;
    bool noKeyWasPressed = true;
    sf::Clock frameClock;
    sf::Time frameTime = frameClock.restart();
    sf::Vector2f movement(0.f, 0.f);

    if(input->isActionTriggered(Inputs::Space))
    {
        speed = 120.0f;
        if(input->isActionTriggered(Inputs::Up))
        {
            currentAnimation = &walkingAnimationUp;
            movement.y -= speed;
            noKeyWasPressed = false;
        }
        if(input->isActionTriggered(Inputs::Down))
        {
            currentAnimation = &walkingAnimationDown;
            movement.y += speed;
            noKeyWasPressed = false;
        }
        if(input->isActionTriggered(Inputs::Left))
        {
            currentAnimation = &walkingAnimationLeft;
            movement.x -= speed;
            noKeyWasPressed = false;
        }
        if(input->isActionTriggered(Inputs::Right))
        {
            currentAnimation = &walkingAnimationRight;
            movement.x += speed;
            noKeyWasPressed = false;
        }
    }
        else
        {
            speed = 80.0f;
            if(input->isActionTriggered(Inputs::Up))
            {
                currentAnimation = &walkingAnimationUp;
                movement.y -= speed;
                noKeyWasPressed = false;
            }
            if(input->isActionTriggered(Inputs::Down))
            {
                currentAnimation = &walkingAnimationDown;
                movement.y += speed;
                noKeyWasPressed = false;
            }
            if(input->isActionTriggered(Inputs::Left))
            {
                currentAnimation = &walkingAnimationLeft;
                movement.x -= speed;
                noKeyWasPressed = false;
            }
            if(input->isActionTriggered(Inputs::Right))
            {
                currentAnimation = &walkingAnimationRight;
                movement.x += speed;
                noKeyWasPressed = false;
            }
        }

        animatedSprite.play(*currentAnimation);
        animatedSprite.move(movement * frameTime);

        if(noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;
        animatedSprite.update(frameTime);
}

void Player::Draw()
{
    pWindow->Draw(AnimatedSprite);
}
