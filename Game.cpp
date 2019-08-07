#include"../include/Game.hpp"
#include"../include/AssetManager.hpp"
#include"../include/InputManager.hpp"
#include"../include/AnimatedSprite.hpp"
#include"../include/TileMap.hpp"

Game::Game()
{
    //Window stuff
    m_pWindow = new sf::RenderWindow({screenDimensions.x, screenDimensions.y}, gameName + clientVersion, 1 << 2);
    m_pWindow->setFramerateLimit(60);

    //UI Stuff
    fpsCounter.setFont(*AssetManager::getInstance()->requestFont("TimesNewRoman"));
    fpsCounter.setCharacterSize(36);
    fpsCounter.setFillColor(sf::Color::Red);
    fpsCounter.setPosition(1114, 20);

    sprintOption.setFont(*AssetManager::getInstance()->requestFont("TimesNewRoman"));
    sprintOption.setString("Hold Space to sprint!");
    sprintOption.setCharacterSize(36);
    sprintOption.setFillColor(sf::Color::White);
    sprintOption.setPosition(0, 0);

    //Animation Setup
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

    Background.setTexture(*AssetManager::getInstance()->requestTexture("testBackground"));

    animatedSprite.setPosition(sf::Vector2f(screenDimensions / 2.0f));

    gameWorld.setSize(sf::Vector2f(screenDimensions.x, screenDimensions.y));
    UI.setSize(sf::Vector2f(screenDimensions.x, screenDimensions.y));

    InputManager::getInstance()->addAction(Inputs::Up, sf::Keyboard::Key::Up);
    InputManager::getInstance()->addAction(Inputs::Down, sf::Keyboard::Key::Down);
    InputManager::getInstance()->addAction(Inputs::Left, sf::Keyboard::Key::Left);
    InputManager::getInstance()->addAction(Inputs::Right, sf::Keyboard::Key::Right);
    InputManager::getInstance()->addAction(Inputs::Space, sf::Keyboard::Key::Space);
    InputManager::getInstance()->addAction(Inputs::O, sf::Keyboard::Key::O);
}

Game::~Game()
{
    delete m_pWindow;
    m_pWindow = nullptr;

    AssetManager::getInstance()->cleanUp();
}

void Game::Run()
{
    sf::Clock clock;
    float deltaTime{  };

    bool isRunning = true;
    while(isRunning)
    {
        //Calculate time between frames
        deltaTime = clock.restart().asSeconds();
        //Check events
        isRunning = processEvents();
        if(!isRunning)
        {
            return;
        }
        //Update
        Update(deltaTime);
        frameTime = frameClock.restart();

        //FPS Counter Calc
        FPS = 1.f / deltaTime;
        fpsCounter.setString("FPS: " + std::to_string(FPS));

        //Draw/Render
        Draw();
    }
}

bool Game::processEvents()
{
    sf::Event event;
    while(m_pWindow->pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            m_pWindow->close();
            return false;
        }
    }
    return true;
}

void Game::Update(float deltaTime)
{
    auto input = InputManager::getInstance();

    float speed = 80.0f;
    bool noKeyWasPressed = true;

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
        animatedSprite.move(movement * deltaTime);

        if(noKeyWasPressed)
        {
            animatedSprite.stop();
        }
        noKeyWasPressed = true;
        animatedSprite.update(frameTime);

        gameWorld.setCenter(animatedSprite.getPosition());
        UI.setCenter(screenDimensions.x / 2, screenDimensions.y / 2);
}

void Game::Draw()
{
    m_pWindow->clear();
    m_pWindow->setView(gameWorld);
    m_pWindow->draw(Background);
    m_pWindow->draw(animatedSprite);
    m_pWindow->setView(UI);
    m_pWindow->draw(fpsCounter);
    m_pWindow->draw(sprintOption);
    m_pWindow->display();
}
