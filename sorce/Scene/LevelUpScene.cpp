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
	mainView(Framework::GetView()),spickup(PickupTypes::Ammo())
{

}

bool LevelUpScene::Init()
{
	bg.setTexture(TextureHolder::getTexture("graphics/background.png"));

	textLevel.setFont(FontHolder::getfont("fonts/zombiecontrol.ttf"));
	textLevel.setCharacterSize(90);
	textLevel.setFillColor(Color::White);
	textLevel.setPosition(150, 260);
	textLevel.setString("1- Increased rate of fire""\n2- Increased clip size(next reload)"
		"\n3- Increased max health""\n4- Increased run speed" "\n5- More and better ammo pickups""\n6- More and better health pickups");

	mainView.setCenter(resolution.x * 0.5f, resolution.y * 0.5f);

	return true;
}

void LevelUpScene::Update(Time& dt)
{
	if (InputManager::GetKeyDown(Keyboard::Num1)) {
		player.SpeedUp();
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num2)) {
		GameVal::megazine += 5;
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num3)) {
		player.UpgradeMaxHealth();
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num4)) {
		player.UpgradeSpeed();
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num5)) {
		spickup.AammoUpgrade();
		sceneManager.ChangeScene(SceneType::STAGE);
	}
	if (InputManager::GetKeyDown(Keyboard::Num6)) {
		spickup.HealthUpgrade();
		sceneManager.ChangeScene(SceneType::STAGE);
	}

	// .... 나머지 처리

	//switch (event.type)
	//{
	//case Event::KeyPressed:
	//	switch (event.key.code)
	//	{
	//	case Keyboard::Num1:
	//		//Increased rate of fire
	//		//총알 갯수늘려주기
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num2:
	//		//Increased clip size(next reload)
	//		//탄창늘리기
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num3:
	//		//Increased max health
	//		/*Player.UpgradeMaxHealth();*/
	//		// 플레이어 건강 늘려주기
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num4:
	//		//Increased run speed
	//		//스피드 늘려주기
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num5:
	//		//More and better health pickup
	//		//health 아이템늘려주기
	//		sceneManager.ChangeScene(SceneType::STAGE);
	//		break;
	//	case Keyboard::Num6:
	//		// More and better ammo pickups
	//		//ammo 아이템늘려주기

	//		break;

	//	default:
	//		break;
	//	}
	//	break;
	//}
	if (InputManager::GetKeyDown(Keyboard::Enter)) {
		sceneManager.ChangeScene(SceneType::STAGE);
	}
}

void LevelUpScene::Render()
{
	window.draw(bg);
	window.draw(textLevel);
}

void LevelUpScene::Release()
{
}

LevelUpScene::~LevelUpScene()
{
}
