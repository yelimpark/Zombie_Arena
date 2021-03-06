#include "StageScene.h"

#include "../Framework/Framework.h"

#include "../Player/Player.h"
#include "../Zombie/Zombie.h"
#include "../Bullet/Bullet.h"
#include "../Pickup/Pickup.h"
#include "../Zombie/Blood.h"

#include <iostream>
#include <random>

using namespace sf;

StageScene::StageScene(SceneManager& sceneManager)
	:Scene(sceneManager), zombieCount(GameVal::wave * 10), pause(true),
    resolution(Framework::GetResolution()),
    window(Framework::Getwindow()),
    mainView(Framework::GetGameView()),
    uiView(Framework::GetUIView())
{

}

bool StageScene::Init()
{
    arena.width = 1200.f;
    arena.height = 1200.f;

    zombieCount = GameVal::wave * 10;

    player.Spawn(arena, resolution, 50.f);
    CreateBackground();
    CreateZobies();
    CreateBullets();

    Pickup* ammoPickup = new Pickup(PickupTypes::Ammo);
    items.push_back(ammoPickup);

    Pickup* healthPickup = new Pickup(PickupTypes::Health);
    items.push_back(healthPickup);
    healthBar.Init(player.GetHealth(), resolution);

    for (auto item : items) {
        item->SetArena(arena);
        item->Spawn(true);
    }

    healthBar.Init(player.GetHealth(), resolution);

    pause = false;

	return true;
}

void StageScene::Update(Time& dt)
{
    if (pause) {
        if (player.GetHealth() <= 0 && InputManager::GetKeyDown(Keyboard::Enter)) {
            GameVal::Init();
            sceneManager.ChangeScene(SceneType::TITLE);
        }

        if (InputManager::GetKeyDown(Keyboard::Enter)) {
            pause = false;
        }

        return;
    }

    if (InputManager::GetKeyDown(Keyboard::Enter) ||
        player.GetHealth() <= 0)
    {
        pause = true;
    }

    if (zombieCount <= 0) {
        ++GameVal::wave;
        sceneManager.ChangeScene(SceneType::LEVELUP);
    }

    playTime += dt;

    player.Update(dt.asSeconds());

    for (auto zombie : zombies) {
        zombie->Update(dt.asSeconds(), player.GetPosition());
    }

    for (auto item : items) {
        item->Update(dt.asSeconds(),PickupTypes::Ammo);
        item->Update(dt.asSeconds(),PickupTypes::Health);
    }

    for (auto blood : bloods) {
        blood->Update(dt.asSeconds());
    }

    zombieCount -= player.UpdateCollision(zombies, bloods);

    for (auto zombie : zombies) {
        if (zombie->UpdateCollision(player, playTime)) {
            healthBar.Update(player.GetHealth());
            break;
        }
    }

    if (player.UpdateCollision(items)) {
        healthBar.Update(player.GetHealth());
    }

    ui.Update(zombieCount, player.GetLeftBullets(), resolution);
    mainView.setCenter(player.GetPosition());
}

void StageScene::Render()
{
    window.setView(mainView);
    window.draw(tileMap, &TextureHolder::getTexture("graphics/background_sheet.png"));

    for (auto blood : bloods) {
        blood->Draw(window);
    }

    for (auto item : items) {
        if (item->IsSpawned()) {
            window.draw(item->GetSprite());
        }
    }

    for (auto zombie : zombies) {
        zombie->Draw(window, arena);
    }

    player.Draw(window);

    window.setView(uiView);
    ui.Draw(window);
    healthBar.Draw(window);
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
        if (v != nullptr)
            delete v;
    }

    zombies.clear();

    int offset = 500;
    int minX = arena.left - offset;
    int maxX = arena.width + offset;
    int minY = arena.top - offset;
    int maxY = arena.height + offset;

    for (int i = 0; i < zombieCount; ++i) {
        int x, y;

        if (utils::RandomBool()) {
            x = utils::RandomRange(minX, maxX + 1);
            y = (utils::RandomBool())? utils::RandomRange(minY, arena.top) : utils::RandomRange(arena.height, maxY);
        }
        else {
            x = (utils::RandomBool()) ? utils::RandomRange(minX, arena.left) : utils::RandomRange(arena.width, maxX);
            y = utils::RandomRange(minY, maxY);
        }

        ZombieTypes type = (ZombieTypes)utils::RandomRange(0, (int)ZombieTypes::COUNT);

        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);

        zombies.push_back(zombie);
    }
}

void StageScene::CreateBullets() {
    for (auto v : bullets) {
        if (v != nullptr)
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
    for (auto item : items) {
        if (item != nullptr)
            delete item;
    }

    items.clear();

    for (auto v : zombies) {
        if (v != nullptr)
            delete v;
    }

    zombies.clear();

    for (auto v : bullets) {
        if (v != nullptr)
            delete v;
    }

    bullets.clear();

    for (auto v : bloods) {
        if (v != nullptr)
            delete v;
    }

    bloods.clear();
}

StageScene::~StageScene()
{
    Release();
}
