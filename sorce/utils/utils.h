#pragma once

#include <SFML/Graphics.hpp>
#include <random>

using namespace sf;

// L, C, R
// T, M, B
enum class Pivots {
	LeftTop,
	CenterTop,
	RightTop,
	LeftMiddle,
	Center,
	RightMiddle,
	LeftBottom,
	CenterBottom,
	RightBottom
};

class utils {
private:
	static std::random_device rd;
	static std::mt19937 gen;

public :
	static void SetOrigin(Sprite& sprite, Pivots preset);

	static void SetOrigin(Shape& shape, Pivots preset);

	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);

	static int RandomRange(int min, int max);

	static void NomalizeVector(Vector2f& vector);

	static bool IsPointInArea(const Vector2f& point, float left, float top, float width, float height);

	static bool IsRectInArea(const FloatRect& rect, float left, float top, float width, float height);

};