#include "DestructiveBrick.h"

DestructiveBrick::DestructiveBrick()
{
	brickShape.setFillColor(Color::Red);
	brickShape.setSize(Vector2f(20, 60));
	destructivebrickSpeed = 1.0f;
}

DestructiveBrick::DestructiveBrick(RectangleShape rectangleShape)
{
	brickShape = rectangleShape;
	position = rectangleShape.getPosition();
	destructivebrickSpeed = 1.0f;
}


DestructiveBrick::~DestructiveBrick()
{
}

void DestructiveBrick::update()
{
	brickShape.setPosition(position);
}

void DestructiveBrick::moveDown(float bottomEdge)
{
	if (position.y <= bottomEdge) {
		position.y += destructivebrickSpeed;
	}
}

RectangleShape DestructiveBrick::getShape()
{
	return brickShape;
}

Vector2f DestructiveBrick::getPosition()
{
	return position;
}



