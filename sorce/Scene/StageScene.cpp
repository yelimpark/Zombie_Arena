#include "StageScene.h"

#include "../Framework/Framework.h"

#include "../Player/Player.h"
#include "../Zombie/Zombie.h"
#include "../Bullet/Bullet.h"
#include "../Pickup/Pickup.h"

#include <iostream>
#include <random>

using namespace sf;

StageScene::StageScene(SceneManager& sceneManager)
	:Scene(sceneManager), zombieCount(100),
    resolution(Framework::GetResolution()),
    window(Framework::Getwindow()),
    mainView(Framework::GetView())
{

}

bool StageScene::Init()
{
    arena.width = resolution.x;
    arena.height = resolution.y;

    player.Spawn(arena, resolution, 0.f);
    CreateBackground();
    CreateZobies();
    CreateBullets();

    Pickup* ammoPickup = new Pickup(PickupTypes::Ammo);
    ammoPickup->Spawn(true);
    items.push_back(ammoPickup);

    texBg = TextureHolder::getTexture("graphics/background_sheet.png");

	return true;
}

void StageScene::Update(Time& dt)
{
    playTime += dt;

    player.Update(dt.asSeconds());

    for (auto zombie : zombies) {
        zombie->Update(dt.asSeconds(), player.GetPosition());
    }

    for (auto item : items) {
        item->Update(dt.asSeconds());
    }

    player.UpdateCollision(zombies);
    for (auto zombie : zombies) {
        if (zombie->UpdateCollision(player, playTime)) {
            break;
        }
    }

    player.UpdateCollision(items);

    mainView.setCenter(player.GetPosition());
}

void StageScene::Render()
{
    window.draw(tileMap, &texBg);

    for (auto item : items) {
        if (item->IsSpawned()) {
            window.draw(item->GetSprite());
        }
    }

    for (auto zombie : zombies) {
        zombie->Draw(window);
    }

    player.Draw(window);
}

void StageScene::CreateBackground() {
    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTS_IN_QUAD = 4;

    int cols = arena.width / TILE_SIZE;
    int rows = arena.height / TILE_SIZE;

    tileMap.setPrimitiveType(Quads);
    tileMap.resize(cols * rows * VERTS_IN_QUAD);

    int idx = 0;

    for (int c = 0; c < cols; ++c) {
        for (int r = 0; r < rows; ++r) {
            int idx = r * cols + c;

            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIdx = idx * VERTS_IN_QUAD;

            tileMap[vertexIdx + 0].position = Vector2f(x, y);
            tileMap[vertexIdx + 1].position = Vector2f(x + TILE_SIZE, y);
            tileMap[vertexIdx + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
            tileMap[vertexIdx + 3].position = Vector2f(x, y + TILE_SIZE);

            float texIdx = 0;

            if (c == 0 || r == 0 || c == cols - 1 || r == rows - 1) {
                texIdx = 3;
            }
            else {
                texIdx = utils::RandomRange(0, TILE_TYPES);
            }

            float offset = texIdx * TILE_SIZE;

            tileMap[vertexIdx + 0].texCoords = Vector2f(0.f, offset);
            tileMap[vertexIdx + 1].texCoords = Vector2f(TILE_SIZE, offset);
            tileMap[vertexIdx + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
            tileMap[vertexIdx + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);
        }
    }
}

void StageScene::CreateZobies() {
    for (auto v : zombies) {
        delete v;
    }

    zombies.clear();

    int offset = 25;
    int minX = arena.left + offset;
    int maxX = arena.width - offset;
    int minY = arena.top + offset;
    int maxY = arena.height - offset;

    for (int i = 0; i < zombieCount; ++i) {
        int x = utils::RandomRange(minX, maxX + 1);
        int y = utils::RandomRange(minY, maxY + 1);

        ZombieTypes type = (ZombieTypes)utils::RandomRange(0, (int)ZombieTypes::COUNT);

        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);

        zombies.push_back(zombie);
    }
}

void StageScene::CreateBullets() {
    for (auto v : bullets) {
        delete v;
    }

    bullets.clear();

    for (int i = 0; i < 1000; ++i) {
        Bullet* bullet = new Bullet();
        bullets.push_back(bullet);
    }
}

void StageScene::Release()
{
}

StageScene::~StageScene()
{
}
