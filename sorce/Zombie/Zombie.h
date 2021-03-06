#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player;

enum class ZombieTypes {
	BLOATER,
	CHASER,
	CRAWLER,
	COUNT
};

struct ZombieInfo {
	ZombieTypes type;
	std::string textureFilename;
	float speed;
	int health;
	int score;
};

class Zombie {
private:
	ZombieTypes zombieTypes;

	Vector2f position;
	Sprite sprite;

	float speed;
	int health;
	int score;

	bool Isdead;

	static std::vector<ZombieInfo> zombieInfo;
	static bool isInitzombieInfo;

public:
	Zombie();

	bool OnHitted();
	bool IsAlive();

	void Spawn(float x, float y, ZombieTypes type);
	void Update(float dt, Vector2f playerPosition);

	bool UpdateCollision(Player& player, Time time);

	FloatRect GetGlobalBound();
	Sprite Getsprite();
	Vector2f GetPosition();

	void Draw(RenderWindow& window, IntRect& arena);
};