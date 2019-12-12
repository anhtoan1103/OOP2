#include "Paddle.h"

Paddle::Paddle(float startX, float startY)
{
	position.x = startX;
	position.y = startY;
	PaddleShape.setSize(sf::Vector2f(150, 10));
	PaddleShape.setPosition(position);
	PaddleShape.setFillColor(Color(6, 232, 203));
}


FloatRect Paddle::getPosition()
{
	return PaddleShape.getGlobalBounds();
}

RectangleShape Paddle::getShape()
{
	return PaddleShape;
}

void Paddle::moveRight(int right)
{
	isMoveRight = 1;
	if (position.x <= right- 150)
	{
		position.x += PaddleSpeed;
	}
}

void Paddle::moveLeft(int left)
{
	isMoveRight = -1;
	if (position.x>=left)
	{
		position.x -= PaddleSpeed;
	}
}


void Paddle::update()
{
	PaddleShape.setPosition(position);
}


void Paddle::autoMove(int left, int right, Ball ball)
{
	if (position.x + getPosition().width > ball.getPosition().left)
	{
		moveLeft(left);
	}
	else if (position.x < ball.getPosition().left)
	{
		moveRight(right);
	}

	/*if ((position.x + PaddleShape.getSize().x) / 2 < ball.getPosition().left)
	{
		moveRight(right);
	}
	else if ((position.x + PaddleShape.getSize().x) / 2 > ball.getPosition().left)
	{
		moveLeft(left);
	}*/
}