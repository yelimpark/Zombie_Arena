#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameVal {
public:
	static int wave;
	static int score;
	static int megazine;
	static int hiScore;

	// �׿� ��ȭ Ʈ�� ����

	static void Init();
	void UpdateHScore();
};