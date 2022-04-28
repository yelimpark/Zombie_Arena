#include "TitleScene.h"
#include "../utils/TextureHolder.h"
#include "../Framework/Framework.h"

TitleScene::TitleScene(SceneManager& sceneManager)
	:Scene(sceneManager),
	window(Framework::Getwindow())
{
}

bool TitleScene::Init()
{
	bg.setTexture(TextureHolder::getTexture("graphics/background.png"));
	return true;
}

void TitleScene::Update(Time& dt)
{
}

void TitleScene::Render()
{
	window.draw(bg);
}

void TitleScene::Release()
{
}

TitleScene::~TitleScene()
{
}
