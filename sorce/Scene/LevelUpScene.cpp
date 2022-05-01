#include "LevelUpScene.h"
#include "../Bullet/Bullet.h"
#include "../utils/TextureHolder.h"
#include "../utils/InputManager.h"
#include "../Framework/Framework.h"
#include"../utils/SceneManager.h"
#include <iostream>
#include <sstream>

using namespace std;

LevelUpScene::LevelUpScene(SceneManager& sceneManager)
	:Scene(sceneManager),
	window(Framework::Getwindow()),
	resolution(Framework::GetResolution()),
	mainView(Framework::GetGameView()),pickup(PickupTypes::Count)
{

}

bool LevelUpScene::Init()
{
	bg.setTexture(TextureHolder::getTexture("graphics/background.png"));

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		menu[i].setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
		menu[i].setFillColor(Color::Red);
		menu[i].setCharacterSize(90);
	}
	
	menu[0].setString("1- Increased rate of fire");
	menu[0].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 4) * 1);

	menu[1].setString("\n2- Increased clip size(next reload)");
	menu[1].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 1) * 1);

	menu[2].setString("\n3- Increased max health");
	menu[2].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 1) * 2);
	
	menu[3].setString("\n4- Increased run speed");
	menu[3].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 1) * 3);
	
	menu[4].setString("\n5- More and better ammo pickups");
	menu[4].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 1) * 4);

	menu[5].setString("\n6- More and better health pickups");
	menu[5].setPosition(150, 1080 / (MAX_NUMBER_OF_ITEMS + 1) * 5);
	

	selectIndex = 0;

	mainView.setCenter(resolution.x * 0.5f, resolution.y * 0.5f);


	return true;
}

void LevelUpScene::Update(Time& dt)
{

	if (InputManager::GetKeyDown(Keyboard::Up))
	{
		MoveUp();
	}
	if (InputManager::GetKeyDown(Keyboard::Down))
	{
		MoveDown();
	}
	if (InputManager::GetKeyDown(Keyboard::Enter))
	{
		switch (GetPressedMenu())
		{
		case 0:
			//firerate
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		case 1:
			GameVal::megazine += 5;
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		case 2:
			player.UpgradeMaxHealth();
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		case 3:
			player.UpgradeSpeed();
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		case 4:
			pickup.Update(2.f, PickupTypes::Ammo);
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		case 5:
			pickup.Update(2.f, PickupTypes::Health);
			sceneManager.ChangeScene(SceneType::STAGE);
			break;
		}
	}

}

void LevelUpScene::MoveUp()
{
	if (selectIndex - 1 >= 0)
	{
		menu[selectIndex].setFillColor(Color::Red);
		selectIndex--;
		menu[selectIndex].setFillColor(Color::White);
	}
}

void LevelUpScene::MoveDown()
{
	if (selectIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectIndex].setFillColor(Color::Red);
		selectIndex++;
		menu[selectIndex].setFillColor(Color::White);
	}
}

void LevelUpScene::Render()
{
	window.draw(bg);

	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void LevelUpScene::Release()
{
}

int LevelUpScene::GetPressedMenu()
{
	return selectIndex;
}

LevelUpScene::~LevelUpScene()
{
}
