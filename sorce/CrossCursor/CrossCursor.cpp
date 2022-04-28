#include "CrossCursor.h"
#include "../Framework/Framework.h"

CrossCursor::CrossCursor()
    :window(Framework::Getwindow())
{
}

void CrossCursor::Init()
{
    window.setMouseCursorVisible(false);
    Texture textureCrosshair = TextureHolder::getTexture("graphics/crosshair.png");
    sprite.setTexture(textureCrosshair);
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

