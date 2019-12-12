#pragma once
#include "Header.h"
#include <SFML/Graphics.hpp>

using namespace sf;

extern char arr[];

class Paddle;
class Ball
{
private:
	Vector2f position; //Vi tri cua trai banh
	CircleShape ballShape;
	float vx = 0.4; //Toc do cua canh ngang
	float vy = 0.4; //Toc do cua canh doc
	int score = 0 ; //Diem ban dau cua trai banh
	int radius = 10; //Ban kinh cua trai bong
public:
	vector <RectangleShape> Brick;
	vector <RectangleShape> ImmortalBrick;
	int test=0;
	CircleShape Gift1;
	CircleShape Gift2;
	CircleShape Gift3;
	int selectedItem = 1;
	int iPos = 0;
public:

	Ball(float initX, float initY); //Khoi tao trai banh

	FloatRect getPosition(); //Lay vi tri trai banh

	CircleShape getShape(); //Lay hinh trai banh

	float getvx(); //Lay van toc ngang

	float getvy(); //Lay vann toc doc

	void setSpeed(); //Lay toc do trai banh

	void hitSides(); //Xu li khi cham 2 bien

	void hitPaddle2(Paddle temp); //Xu li khi cham thanh 2

	void hitRight(); //xu li va cham thanh ben phai

	void hitLeft(); //xu li va cham thanh ben trai

	void hitRightBrick();// Xu li thanh cham ben phai brick

	void hitLeftBrick();// Xu li thanh cham ben trai brick

	void hitTopBrick();// Xu li thanh cham ben tren brick

	FloatRect getRectanglePositionBall();

	void hitBotBrick();// Xu li thanh cham ben duoi brick

	void updatePosition(); //Cap nhat vi tri banh

	int move(int WIDTH, int HEIGH, Paddle paddle2, RenderWindow& window); //Di chuyen trai banh

	int getScorePalyer2(); //Lay diem cua nguoi thu 2

	void readFile(int& i, int& j, string file_name);

	bool isExistBrick(Vector2f position, vector<RectangleShape> Brick);

	void setItem();

	void drawItem(RenderWindow& window);

	int drawItemOnMap(RenderWindow& window, vector<RectangleShape> Brick);

	void defaultItem(Vector2f position, RenderWindow& window);

};
