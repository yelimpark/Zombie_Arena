#include "utils.h"

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
