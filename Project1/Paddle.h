#pragma once
#include "Header.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Ball;
class Paddle
{
private:
	Vector2f position; //Vi tri cua thanh truot
	RectangleShape PaddleShape; //Hinh dang cua thanh
	float PaddleSpeed = 1.5f; //Van toc ban dau cua thanh
	
public:

	int isMoveRight = -1;

	Paddle(float startX, float startY); //Khoi tao thanh

	FloatRect getPosition();

	RectangleShape getShape();

	void moveLeft(int left); //Ham di chuyen sang trai

	void moveRight(int right); //Ham di chuyen sang phai

	void update(); //ham cap nhat trang thai cua thanh

	void autoMove(int Top, int Bot, Ball ball); //Ham tu choi cua BOT

	void setPaddleSpeed(float speed);
};