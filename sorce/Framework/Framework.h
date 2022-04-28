#pragma once
#include "../utils/TextureHolder.h"
#include "../utils/utils.h"
#include "../utils/InputManager.h"
#include "../utils/SceneManager.h"
#include "../CrossCursor/CrossCursor.h"

using namespace sf;

class Framework {
private:
    static Vector2i resolution;
    static RenderWindow window;
    static View mainView;

    TextureHolder textureHolder;
    SceneManager sMgr;

    CrossCursor crossCursor;

    Clock clock;

    static Framework* FrameInstance;

public:
    Framework();

    static RenderWindow& Getwindow();

    static const Vector2i& GetResolution();

    static View& GetView();

    void Init();

    int Run();

    ~Framework();
};