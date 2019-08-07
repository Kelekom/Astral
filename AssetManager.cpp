#include"AssetManager.hpp"
#include"AnimatedSprite.hpp"
using namespace std;

AssetManager::AssetManager()
{
    loadTexture("Game Assets/Character Sprites/Celes/Celes Walking.png", "celesWalking");
    loadTexture("Game Assets/Character Sprites/Cyan/Cyan Walking.png", "cyanWalking");
    loadTexture("Game Assets/Character Sprites/Edgar/Edgar Walking.png", "edgarWalking");
    loadTexture("Game Assets/Character Sprites/Locke/Locke Walking.png", "lockeWalking");
    loadTexture("Game Assets/Character Sprites/Sabin/Sabin Walking.png", "sabinWalking");
    loadTexture("Game Assets/Character Sprites/Shadow/Shadow Walking.png", "shadowWalking");
    loadTexture("Game Assets/Maps/ff4map_wsc02.png", "testBackground");

    loadFont("Game Assets/Fonts/TimesNewRomanMTStd-Bold.otf", "TimesNewRoman");
}

void AssetManager::loadTexture(string path, string name)
{
    sf::Texture* t = new sf::Texture;
    t->loadFromFile(path);

    Textures[name] = t;
}

void AssetManager::cleanUp()
{
    for(auto item: Textures)
    {
        delete item.second;
        item.second = nullptr;
    }
}

AssetManager::~AssetManager()
{

}

sf::Texture* AssetManager::requestTexture(string name)
{
    if(Textures[name])
    {
        return Textures[name];
    }
    return nullptr;
}

void AssetManager::loadFont(string path, string name)
{
    sf::Font* f = new sf::Font;
    f->loadFromFile(path);

    Fonts[name] = f;
}

sf::Font* AssetManager::requestFont(string name)
{
    if(Fonts[name])
    {
        return Fonts[name];
    }
    return nullptr;
}

