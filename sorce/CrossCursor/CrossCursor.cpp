#include "CrossCursor.h"
#include "../Framework/Framework.h"

CrossCursor::CrossCursor()
    :window(Framework::Getwindow())
{
}

void CrossCursor::Init()
{
    window.setMouseCursorVisible(false);
    sprite.setTexture(TextureHolder::getTexture("graphics/crosshair.png"));
    utils::SetOrigin(sprite, Pivots::Center);
}

void CrossCursor::Update()
{
    sprite.setPosition(InputManager::GetMouseWorldPosition());
}

void CrossCursor::Render()
{
    window.draw(sprite);
}

CrossCursor::~CrossCursor()
{
}

