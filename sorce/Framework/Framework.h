#pragma once
#include "../utils/TextureHolder.h"
#include "../utils/FontHolder.h"
#include "../utils/utils.h"
#include "../utils/InputManager.h"
#include "../utils/SceneManager.h"
#include "../CrossCursor/CrossCursor.h"

using namespace sf;

class Framework {
private:
    static Vector2i resolution;
    static RenderWindow window;
    static View GameView;
    static View uiView;

    TextureHolder textureHolder;
    FontHolder fontHolder;
    SceneManager sMgr;

    CrossCursor crossCursor;

    Clock clock;

    static Framework* FrameInstance;

public:
    Framework();

    static RenderWindow& Getwindow();

    static const Vector2i& GetResolution();

    static View& GetGameView();

    static View& GetUIView();

    void Init();

    int Run();

    ~Framework();
};