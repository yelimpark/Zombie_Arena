#include "utils.h"

std::random_device utils::rd;
std::mt19937 utils::gen(rd());

void utils::SetOrigin(Sprite& sprite, Pivots preset)
{
	SetOrigin(sprite, sprite.getLocalBounds(), preset);
}

void utils::SetOrigin(Shape& shape, Pivots preset)
{
	SetOrigin(shape, shape.getLocalBounds(), preset);
}

void utils::SetOrigin(Transformable& tr, FloatRect bounds, Pivots preset)
{
	switch (preset)
	{
	case Pivots::LeftTop:
		tr.setOrigin(0, 0);
		break;
	case Pivots::CenterTop:
		tr.setOrigin(bounds.width * 0.5f, 0);
		break;
	case Pivots::RightTop:
		tr.setOrigin(bounds.width, 0);
		break;
	case Pivots::LeftMiddle:
		tr.setOrigin(0, bounds.height * 0.5f);
		break;
	case Pivots::Center:
		tr.setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
		break;
	case Pivots::RightMiddle:
		tr.setOrigin(bounds.width, bounds.height * 0.5f);
		break;
	case Pivots::LeftBottom:
		tr.setOrigin(0, bounds.height);
		break;
	case Pivots::CenterBottom:
		tr.setOrigin(bounds.width * 0.5f, bounds.height);
		break;
	case Pivots::RightBottom:
		tr.setOrigin(bounds.width, bounds.height);
		break;
	default:
		break;
	}
}

int utils::RandomRange(int min, int max)
{
	return gen() % (max - min) + min;
}

bool utils::RandomBool()
{
	return (gen() % 2 == 1)? true : false;
}

Vector2f utils::NomalizeVector(Vector2f vector)
{
	float length = GetLength(vector);

	if (length > 0) {
		vector /= length;
	}

	return vector;
}

bool utils::IsPointInArea(const Vector2f& point, float left, float top, float width, float height)
{
	FloatRect area;
	area.left = left;
	area.top = top;
	area.width = width;
	area.height = height;

	return area.contains(point);
}

bool utils::IsRectInArea(const FloatRect& rect, float left, float top, float width, float height)
{
	FloatRect area;
	area.left = left;
	area.top = top;
	area.width = width;
	area.height = height;

	return area.intersects(rect);
}

float utils::GetLength(const Vector2f& vector)
{
	return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float utils::GetAngle(const Vector2f& from, const Vector2f& to)
{
	Vector2f dir = to - from;
	float radian = atan2(dir.y, dir.x);
	return radian * 180.f / 3.141592f;
}
