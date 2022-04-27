#include <SFML/Graphics.hpp>
#include "utils/TextureHolder.h"
#include "utils/utils.h"
#include "utils/InputManager.h"
#include "utils/SceneManager.h"

using namespace sf;

int main()
{
    TextureHolder textureHolder;

    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);

    //cursor
    window.setMouseCursorVisible(false);
    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::getTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    utils::SetOrigin(spriteCrosshair, Pivots::Center);

    InputManager::Init();

    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    Clock clock;

    SceneManager sMgr;
    sMgr.Init();
    
    while (window.isOpen())
    {
        Time dt = clock.restart();
        sMgr.Update(dt.asSeconds());

        window.clear();
        sMgr.Render(window);

        window.draw(spriteCrosshair);

        window.display();
    }

    return 0;
}