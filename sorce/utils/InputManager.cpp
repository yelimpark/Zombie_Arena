#include "InputManager.h"
#include <algorithm>

map<Axis, AxisInfo> InputManager::mapAxis;
list<Keyboard::Key> InputManager::downKeys;
list<Keyboard::Key> InputManager::ingKeys;
list<Keyboard::Key> InputManager::upKeys;

void InputManager::Init()
{
    mapAxis.clear();

    AxisInfo info;

    info.axis = Axis::Horizonal;
    info.positiveKeys.clear();
    info.positiveKeys.push_back(Keyboard::D);
    info.positiveKeys.push_back(Keyboard::Right);

    info.negativeKeys.clear();
    info.negativeKeys.push_back(Keyboard::A);
    info.negativeKeys.push_back(Keyboard::Left);
    mapAxis[info.axis] = info;

    info.axis = Axis::Vertical;
    info.positiveKeys.clear();
    info.positiveKeys.push_back(Keyboard::S);
    info.positiveKeys.push_back(Keyboard::Down);

    info.negativeKeys.clear();
    info.negativeKeys.push_back(Keyboard::W);
    info.negativeKeys.push_back(Keyboard::Up);
    mapAxis[info.axis] = info;
}

int InputManager::GetAxis(Axis axis)
{
    auto pair = mapAxis.find(axis);
    if (pair != mapAxis.end()) {
        return GetAxis(pair->second.positiveKeys, pair->second.negativeKeys);
    }
    return 0;
}

int InputManager::GetAxis(const list<Keyboard::Key>& positive,const list<Keyboard::Key>& nagative)
{
    int axis = 0;

    bool isPositive = false;
    bool isNegative = false;

    for (auto it = positive.cbegin(); it != positive.cend(); ++it) {
        Keyboard::Key key = (*it);
        if (Keyboard::isKeyPressed(key)) {
            isPositive = true;
            break;
        }
    }

    for (auto it = nagative.cbegin(); it != nagative.cend(); ++it) {
        Keyboard::Key key = (*it);
        if (Keyboard::isKeyPressed(key)) {
            isNegative = true;
            break;
        }
    }

    if (isPositive && isNegative) {
        axis = 0;
    }
    else if (isNegative) {
        axis = -1;
    }
    else if (isPositive) {
        axis = 1;
    }

    return axis;
}

void InputManager::ProcessInput(const Event& event)
{
    switch (event.type)
    {
    case Event::KeyPressed:
        if (!GetKey(event.key.code)) {
            downKeys.push_back(event.key.code);
            ingKeys.push_back(event.key.code);
        }
        break;
    case Event::KeyReleased:
        ingKeys.remove(event.key.code);
        upKeys.push_back(event.key.code);
        break;
    default:
        break;
    }
}

bool InputManager::GetKeyDown(Keyboard::Key key)
{
    auto it = find(downKeys.begin(), downKeys.end(), key);
    return it != downKeys.end();
}

bool InputManager::GetKey(Keyboard::Key key)
{
    auto it = find(ingKeys.begin(), ingKeys.end(), key);
    return it != ingKeys.end();
}

bool InputManager::GetKeyUp(Keyboard::Key key)
{
    auto it = find(upKeys.begin(), upKeys.end(), key);
    return it != upKeys.end();
}

void InputManager::ClearInput()
{
    downKeys.clear();
    upKeys.clear();
}

Vector2i InputManager::GetMousePosition()
{
    return Mouse::getPosition();
}
