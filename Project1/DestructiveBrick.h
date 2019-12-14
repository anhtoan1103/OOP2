#pragma once
#include "Header.h"
class DestructiveBrick
{
private:
	RectangleShape brickShape;
	Vector2f position;
	float destructivebrickSpeed = 1.0f;
public:
	DestructiveBrick();
	DestructiveBrick(RectangleShape rectangleShape);
	~DestructiveBrick();
	void update();
	void moveDown(float bottomEdge);
	RectangleShape getShape();
	Vector2f getPosition();
};

