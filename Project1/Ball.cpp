#include "Ball.h"
#include <time.h>
#include "Constants.h"


Ball::Ball(float initX, float initY)
{
	srand(time(NULL));

	int count = 0;
	int i = 0, j = 0;
	readFile(i, j, "2.txt");
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)
		{
			if ((int)arr[b + a * j] == 126)
			{
				RectangleShape brick;
				Brick.push_back(brick);
				Brick[count].setPosition(Vector2f((1366 / j) * b, 60 + 22 * a));
				Brick[count].setSize(Vector2f(1366 / j - 2, 20));
				Brick[count].setFillColor(Color::Red);
				count++;
			}
			else
				if ((int)arr[b + a * j] == 45)
				{
					RectangleShape brick;
					Brick.push_back(brick);
					Brick[count].setPosition(Vector2f((1366 / j) * b, 60 + 22 * a));
					Brick[count].setSize(Vector2f(1366 / j - 2, 20));
					Brick[count].setFillColor(Color::Green);
					count++;
				}
		}
	}
	position.x = initX;
	position.y = initY;
	ballShape.setRadius(10);
	ballShape.setPosition(position);
	ballShape.setFillColor(Color::Red);

	Texture* gift1Texture = new Texture;
	Texture* gift2Texture = new Texture;
	Texture* gift3Texture = new Texture;
	Texture* gift4Texture = new Texture;
	gift1Texture->loadFromFile("electric.png");
	gift2Texture->loadFromFile("rock.png");
	gift3Texture->loadFromFile("fighting.png");
	gift4Texture->loadFromFile("fire.png");

	Gift1.setTexture(gift1Texture);
	Gift2.setTexture(gift2Texture);
	Gift3.setTexture(gift3Texture);
	Gift4.setTexture(gift4Texture);

	Gift1.setRadius(25);
	Gift2.setRadius(25);
	Gift3.setRadius(25);
	Gift4.setRadius(25);

	Gift4.setPosition(Vector2f(650, 450));
	selectedItem = 4;

	winBrick.setSize(Vector2f(65, 20));
	winBrick.setFillColor(Color::Yellow);
	winBrick.setPosition(Vector2f((1300 + 65) / 2, 40));
}

FloatRect Ball::getPosition()
{
	return ballShape.getGlobalBounds();
}

CircleShape Ball::getShape()
{
	return ballShape;
}

float Ball::getvx()
{
	return vx;
}

float Ball::getvy()
{
	return vy;
}

void Ball::hitSides()
{
	vy = -vy;
}

void Ball::hitPaddle2(Paddle temp)
{
	setSpeed();
	vy = -vy;
}

void Ball::hitRight()
{
	if (vx > 0)
	{
		vx = -vx;
	}
}

void Ball::hitLeft()
{
	if (vx < 0)
	{
		vx = -vx;
	}

}

void Ball::hitRightBrick()
{
	vx = -vx;
}

void Ball::hitLeftBrick()
{
	score++;
	vx = -vx;
}

void Ball::hitTopBrick()
{
	vy = -vy;
}

void Ball::hitBotBrick()
{
	score++;
	vy = -vy;
}

void Ball::updatePosition()
{
	position.x = position.x + vx;
	position.y = position.y + vy;
	ballShape.setPosition(position);

}

FloatRect Ball::getRectanglePositionBall()
{
	return ballShape.getGlobalBounds();
}

int Ball::move(int WIDTH, int HEIGHT, Paddle paddle2, RenderWindow& window, vector<DestructiveBrick> &VectorDestructiveBrick)
{
	for (int i = 0; i < Brick.size(); i++)
	{
		//Bong cham cuc gach
		if (getPosition().intersects(Brick[i].getGlobalBounds()))
		{
			if (ballShape.getGlobalBounds().top <= Brick[i].getGlobalBounds().top)
			{
				hitLeftBrick();
				if (Brick[i].getFillColor() == Color::Red) {
					Brick[i].setFillColor(Color::Green);
				}
				else if (Brick[i].getFillColor() == Color::Green) {
					Brick.erase(Brick.begin() + i);
				}
			}
			else
			{
				hitBotBrick();
				if (Brick[i].getFillColor() == Color::Red) {
					Brick[i].setFillColor(Color::Green);
				}
				else if (Brick[i].getFillColor() == Color::Green) {
					Brick.erase(Brick.begin() + i);
				}
			}
		}
	}
	//Bong cham vat pham 1
	if (getPosition().intersects(Gift1.getGlobalBounds()) && selectedItem == 1)
	{
		// Item co chuc nang nhan x2 diem dang co
		score *= 2;
		setItem();
	}
	//Bong cham vat pham 2
	if (getPosition().intersects(Gift2.getGlobalBounds()) && selectedItem == 2)
	{
		// Item co chuc nang tao ra 1 vat pham khong the bi pha huy
		setImmortalBrick();
		setItem();
	}
	//Bong cham vat pham 3
	if (getPosition().intersects(Gift3.getGlobalBounds()) && selectedItem == 3)
	{
		score *= 0.5;
		setItem();
	}
	//Bong cham vat pham 4
	if (getPosition().intersects(Gift4.getGlobalBounds()) && selectedItem == 4)
	{
		RectangleShape brick;
		brick.setFillColor(Color::Red);
		brick.setSize(Vector2f(20, 60));
		brick.setPosition(Vector2f(rand() % 1280, 0));
		
		VectorDestructiveBrick.push_back(DestructiveBrick(brick));
		setItem();
	}
	//Bong cham paddle
	if (getPosition().intersects(paddle2.getPosition()))
	{
		hitPaddle2(paddle2);
	}
	//Dung vao cuc gach trang
	for (int i = 0; i < ImmortalBrick.size(); i++)
	{
		if (getPosition().intersects(ImmortalBrick[i].getGlobalBounds()))
		{
			if (ballShape.getGlobalBounds().top <= ImmortalBrick[i].getGlobalBounds().top)
			{
				hitLeftBrick();
				score--;
			}
			else
			{
				hitBotBrick();
				score--;
			}
		}
	}
	//Bong cham bien ngang tren
	if (getPosition().top < 0)
	{
		hitSides();
	}
	//Bong cham bien phai
	if (getPosition().left +ballShape.getRadius()*2 > WIDTH)
	{
		hitRight();
	}
	//Bong cham bien trai
	if (getPosition().left < 0)
	{
		hitLeft();
	}
	//Bong cham bien ngang duoi thi thua
	if (getPosition().height + getPosition().top > HEIGHT)
	{
		return 1;
	}
	for (int i = 0; i < VectorDestructiveBrick.size(); i++) {
		//Paddle cham vao cuc gach huy diet thi thua
		if (VectorDestructiveBrick[i].getShape().getGlobalBounds().intersects(paddle2.getPosition())) {
			return 1;
		}
	}
	//Het gach thi thang
	if (Brick.size() == 0) {
		return 2;
	}
	//Dung vao cuc gach vang thi thang
	if (getRectanglePositionBall().intersects(winBrick.getGlobalBounds())) {
		return 2;
	}
}

void Ball::setSpeed()
{
	if (vx <= 0)
	{
		vx = vx - 0.02;
	}
	else if (vx >= 0)
	{
		vx = vx + 0.02;
	}
	if (vy <= 0)
	{
		vy = vy - 0.02;
	}
	else if (vy >= 0)
	{
		vy = vy + 0.02;
	}
}


int Ball::getScorePalyer2()
{
	return score;
}

void Ball::readFile(int& i, int& j, string file_name)
{
	ifstream file;
	file.open(file_name);
	char a[250];
	string s;

	while (!file.eof())
	{
		file.getline(a, 250);
		s = a;
		if (j < s.length())
		{
			j = s.length();
		}
		i++;
	}
	file.close();
	file.open(file_name);
	int c = 0, d = 0;
	while (!file.eof())
	{
		file.getline(a, 250);

		for (c = 0; c < j; c++)
		{
			arr[c + d * j] = a[c];
		}
		d++;
	}
	file.close();
}

void Ball::draw(RenderWindow& window)
{
	window.draw(ballShape);
	window.draw(winBrick);
	if (selectedItem == 1)
	{
		window.draw(Gift1);
	}
	else if (selectedItem == 2)
	{
		window.draw(Gift2);
	}
	else if (selectedItem == 3)
	{
		window.draw(Gift3);
	}
	else if (selectedItem == 4)
	{
		window.draw(Gift4);
	}
	for (int i = 0; i < Brick.size(); i++)
	{
		window.draw(Brick[i]);
	}
	for (int i = 0; i < ImmortalBrick.size(); i++) {
		window.draw(ImmortalBrick[i]);
	}
}

bool Ball::isIntersectBrick(RectangleShape brick)
{
	for (int i = 0; i < Brick.size(); i++) {
		if (brick.getGlobalBounds().intersects(Brick[i].getGlobalBounds())) {
			return 1;
		}
	}
	return 0;
}

bool Ball::isIntersectBrick(CircleShape gift)
{
	for (int i = 0; i < Brick.size(); i++) {
		if (gift.getGlobalBounds().intersects(Brick[i].getGlobalBounds())) {
			return 1;
		}
	}
	return 0;
}

void Ball::setItem()
{
	selectedItem = rand() % 4 + 1;
	Vector2f positionGift = Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1));
	if (selectedItem == 1)
	{
		Gift1.setPosition(positionGift);
		if (isIntersectBrick(Gift1)) {
			setItem();
		}
	}
	else if (selectedItem == 2)
	{
		Gift2.setPosition(positionGift);
		if (isIntersectBrick(Gift2)) {
			setItem();
		}
	}
	else if (selectedItem == 3)
	{
		Gift3.setPosition(positionGift);
		if (isIntersectBrick(Gift3)) {
			setItem();
		}
	}
	else if (selectedItem == 4)
	{
		Gift4.setPosition(positionGift);
		if (isIntersectBrick(Gift4)) {
			setItem();
		}
	}
}

void Ball::setImmortalBrick()
{
	RectangleShape brick;
	Vector2f positionImmortalBrick = Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1));
	brick.setPosition(positionImmortalBrick);
	if (isIntersectBrick(brick) == 1) {
		setImmortalBrick();
	}

	brick.setSize(Vector2f(65, 20));
	brick.setFillColor(Color::White);
	ImmortalBrick.push_back(brick);
}

void Ball::setWinBrick()
{
	winBrick.setSize(Vector2f(65, 20));
	winBrick.setFillColor(Color::Yellow);
	winBrick.setPosition(Vector2f((1300 + 65) / 2, 40));
}




