#include"InputManager.hpp"

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::addAction(int id, sf::Keyboard::Key key)
{
    m_Actions[id] = key;
}

bool InputManager::isActionTriggered(int id)
{
    return sf::Keyboard::isKeyPressed(m_Actions[id]);
}
