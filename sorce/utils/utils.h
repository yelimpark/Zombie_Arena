#pragma once

#include <SFML/Graphics.hpp>

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
public :
	static void SetOrigin(Sprite& sprite, Pivots preset);

	static void SetOrigin(Shape& shape, Pivots preset);

	static void SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset);
};