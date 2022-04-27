﻿#include <SFML/Graphics.hpp>
#include "./utils/InputManager.h"
#include "./utils/utils.h"
#include "./Player/Player.h"
#include "./utils/TextureHolder.h"
#include "./Zombie/Zombie.h"
#include "./Bullet/Bullet.h"
#include "./Pickup/Pickup.h"

#include <iostream>
#include <random>

using namespace sf;

void CreateBackground(VertexArray& va, IntRect arena) {
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int cols = arena.width / TILE_SIZE;
    int rows = arena.height / TILE_SIZE;

    va.setPrimitiveType(Quads);
    va.resize(cols * rows * VERTS_IN_QUAD);

    int idx = 0;

    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            int idx = r * cols + c;

            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIdx = idx * VERTS_IN_QUAD;

            va[vertexIdx + 0].position = Vector2f(x, y);
            va[vertexIdx + 1].position = Vector2f(x + TILE_SIZE, y);
            va[vertexIdx + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
            va[vertexIdx + 3].position = Vector2f(x, y + TILE_SIZE);

            float texIdx = 0;

            if (c == 0 || r == 0 || c == cols - 1 || r == rows - 1) {
                texIdx = 3;
            }
            else {
                texIdx = utils::RandomRange(0, TILE_TYPES);
            }

            float offset = texIdx * TILE_SIZE;

            va[vertexIdx + 0].texCoords = Vector2f(0.f, offset);
            va[vertexIdx + 1].texCoords = Vector2f(TILE_SIZE, offset);
            va[vertexIdx + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
            va[vertexIdx + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);

        }
    }
}

void CreateZobies(std::vector<Zombie*>& zombies, int count, IntRect arena) {
    for (auto v : zombies) {
        delete v;
    }

    zombies.clear();

    int offset = 25;
    int minX = arena.left + offset;
    int maxX = arena.width - offset;
    int minY = arena.top + offset;
    int maxY = arena.height - offset;

    for (int i = 0; i < count; ++i) {
        int x = utils::RandomRange(minX, maxX + 1);
        int y = utils::RandomRange(minY, maxY + 1);

        ZombieTypes type = (ZombieTypes)utils::RandomRange(0, (int)ZombieTypes::COUNT);

        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);

        zombies.push_back(zombie);
    }
}

void CreateBullets(std::vector<Bullet*>& bullets, int count) {
    for (auto v : bullets) {
        delete v;
    }

    bullets.clear();

    for (int i = 0; i < count; ++i) {
        Bullet* bullet = new Bullet();
        bullets.push_back(bullet);
    }
}

int main()
{
    TextureHolder textureHolder;

    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);

    window.setMouseCursorVisible(false);

    Sprite spriteCrosshair;
    Texture textureCrosshair = TextureHolder::getTexture("graphics/crosshair.png");
    spriteCrosshair.setTexture(textureCrosshair);
    utils::SetOrigin(spriteCrosshair, Pivots::Center);

    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

    InputManager::Init();

    IntRect arena;
    arena.width = resolution.x;
    arena.height = resolution.y;

    Pickup ammoPickup(PickupTypes::Ammo);
    ammoPickup.Spawn(true);

    std::list<Pickup*> items;
    items.push_back(&ammoPickup);

    Player player;
    player.Spawn(arena, resolution, 0.f);

    std::vector<Zombie*> zombies;
    CreateZobies(zombies, 5, arena);

    std::vector<Bullet*> bullets;
    CreateBullets(bullets, 1000);

    bool flag = false;

    std::vector<FloatRect> walls;
    VertexArray tileMap;
    CreateBackground(tileMap, arena);

    Clock clock;
    Time playTime;

    Texture& texBg = TextureHolder::getTexture("graphics/background_sheet.png");

    while (window.isOpen())
    {
        Time dt = clock.restart();
        playTime += dt;

        Event event;

        InputManager::ClearInput();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            InputManager::ProcessInput(event);
        }

        InputManager::Update(dt.asSeconds(), window, mainView);

        player.Update(dt.asSeconds());

        for (auto zombie : zombies) {
            zombie->Update(dt.asSeconds(), player.GetPosition());
        }

        ammoPickup.Update(dt.asSeconds());

        player.UpdateCollision(zombies);
        for (auto zombie : zombies) {
            if (zombie->UpdateCollision(player, playTime)) {
                break;
            }
        }
        player.UpdateCollision(items);

        mainView.setCenter(player.GetPosition());

        spriteCrosshair.setPosition(InputManager::GetMouseWorldPosition());

        window.clear();
        window.setView(mainView);

        // ui

        window.draw(tileMap, &texBg);

        if (ammoPickup.IsSpawned()) {
            window.draw(ammoPickup.GetSprite());
        }

        for (auto zombie : zombies) {
            window.draw(zombie->Getsprite());
        }

        window.draw(player.GetSprite());

        player.Draw(window);

        window.draw(spriteCrosshair);

        window.display();
    }

    return 0;
}