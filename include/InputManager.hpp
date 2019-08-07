#pragma once
#include<SFML/Window/Keyboard.hpp>
#include<map>

enum Inputs
{
    Up,
    Down,
    Left,
    Right,
    Space,
    O
};

class InputManager
{
public:
    static InputManager* getInstance()
    {
        static InputManager instance;
        return &instance;
    }

    virtual ~InputManager();

    void addAction(int id, sf::Keyboard::Key key);
    bool isActionTriggered(int id);

private:
    InputManager();
    std::map<int, sf::Keyboard::Key> m_Actions;
};
