#pragma once
#include<SFML/Graphics.hpp>
#include"AnimatedSprite.hpp"

class Game
{
public:
    Game();
    virtual ~Game();
    void Run();

    const std::string gameName = "Astral Realms";
    const std::string clientVersion = " v0.0.1";
    sf::Vector2f screenDimensions = {1280.0f, 720.0f};


private:
    bool processEvents();
    void Update(float deltaTime);
    void Draw();

private:
    sf::RenderWindow* m_pWindow = nullptr;
    Animation walkingAnimationDown;
    Animation walkingAnimationLeft;
    Animation walkingAnimationRight;
    Animation walkingAnimationUp;
    Animation* currentAnimation = &walkingAnimationDown;
    AnimatedSprite animatedSprite { sf::seconds(0.2), true, false };

    sf::Sprite Background;

    sf::Clock frameClock;
    sf::Time frameTime;

    sf::Text currentSprite;
    int currentSpriteCounter = 1;

    int Temp = 1;


    //UI Stuff
    float currentTime;
    float FPS;
    sf::Text fpsCounter;
    sf::Text sprintOption;
    sf::View UI;

    sf::View gameWorld;
};

