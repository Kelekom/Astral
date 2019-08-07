#pragma once
#include<SFML/Graphics.hpp>
#include<map>
#include"AnimatedSprite.hpp"

class AssetManager
{
public:
    static AssetManager* getInstance()
    {
        static AssetManager instance;
        return &instance;
    }

    void cleanUp();
    virtual ~AssetManager();
    sf::Texture* requestTexture(std::string name);
    sf::Font* requestFont(std::string name);

private:
    AssetManager();
    void loadTexture(std::string path, std::string name);
    void loadFont(std::string path, std::string name);

private:
    std::map<std::string, sf::Texture*> Textures;
    std::map<std::string, sf::Font*> Fonts;
};

