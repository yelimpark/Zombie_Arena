#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameVal {
public:
	static int wave;
	static int score;
	static int megazine;
	static int hiScore;

	// 그외 강화 트리 정보

	static void Init();
	void UpdateHScore();
};