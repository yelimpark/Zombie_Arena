#include <SFML/Graphics.hpp>
#include "./utils/InputManager.h"
#include "./utils/utils.h"
#include "./Player/Player.h"
#include <iostream>

using namespace sf;

int main()
{
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);

    InputManager::Init();

    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    Player player;
    player.Spawn(arena, resolution, 0.f);

    bool flag = false;

    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();

        Event event;

        InputManager::ClearInput();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            InputManager::ProcessInput(event);
        }

        player.Update(dt.asSeconds());

        window.clear();
        window.draw(player.GetSprite());
        window.display();
    }

    return 0;
}