#include "Ball.h"
#include <time.h>

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
	gift1Texture->loadFromFile("fire.png");
	gift2Texture->loadFromFile("rock.png");
	gift3Texture->loadFromFile("fighting.png");

	Gift1.setTexture(gift1Texture);
	Gift2.setTexture(gift2Texture);
	Gift3.setTexture(gift3Texture);

	Gift1.setRadius(25);
	Gift2.setRadius(25);
	Gift3.setRadius(25);

	Gift2.setPosition(Vector2f(650, 450));

	selectedItem = 2;
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

int Ball::move(int WIDTH, int HEIGHT, Paddle paddle2, RenderWindow& window)
{
	for (int i = 0; i < Brick.size(); i++)
	{
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
	if (getPosition().intersects(Gift1.getGlobalBounds()) && selectedItem == 1)
	{
		// Item co chuc nang nhan x2 diem dang co
		score *= 2;
		setItem();
	}

	if (getPosition().intersects(Gift2.getGlobalBounds()) && selectedItem == 2)
	{

		// Item co chuc nang tao ra 1 vat pham khong the bi pha huy
		setImmortalBrick();
		setItem();
	}

	if (getPosition().intersects(Gift3.getGlobalBounds()) && selectedItem == 3)
	{
		score *= 0.5;
		setItem();
	}

	if (getPosition().top < 0)
	{
		hitSides();
	}

	if (getPosition().left +ballShape.getRadius()*2 > WIDTH)
	{
		hitRight();
	}

	if (getPosition().left < 0)
	{
		hitLeft();
	}
	
	if (getPosition().intersects(paddle2.getPosition()))
	{
		if (ballShape.getGlobalBounds().top+ ballShape.getGlobalBounds().height < paddle2.getPosition().top)
		{
			return 1;
		}
		hitPaddle2(paddle2);
	}
	if (getPosition().height + getPosition().top > HEIGHT)
	{
		return 1;
	}

	for (int i = 0; i < ImmortalBrick.size(); i++)
	{
		if (getPosition().intersects(ImmortalBrick[i].getGlobalBounds()))
		{
			if (ballShape.getGlobalBounds().top <= ImmortalBrick[i].getGlobalBounds().top)
			{
				hitLeftBrick();
			}
			else
			{
				hitBotBrick();
			}
		}
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

bool Ball::isExistBrick(Vector2f position, vector<RectangleShape> Brick)
{
	for (int i = 0; i < Brick.size(); i++) {
		if (Brick[i].getPosition() == position) {
			return 1;
		}
	}
	return 0;
}

void Ball::setItem()
{
	selectedItem = rand() % 3 + 1;
	Vector2f positionGift = Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1));
	while (isExistBrick(positionGift, Brick)) {
		positionGift = Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1));
	}
	if (selectedItem == 1)
	{
		Gift1.setPosition(positionGift);
	}
	else if (selectedItem == 2)
	{
		Gift2.setPosition(positionGift);
	}
	else if (selectedItem == 3)
	{
		Gift3.setPosition(positionGift);
	}
}

void Ball::drawItem(RenderWindow& window)
{
	//setItem();
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

void Ball::setImmortalBrick()
{
	RectangleShape brick;
	brick.setSize(Vector2f(65, 20));
	brick.setFillColor(Color::White);

	Vector2f positionImmortalBrick = Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1));
	brick.setPosition(positionImmortalBrick);
	while (isExistBrick(positionImmortalBrick, Brick) || isIntersectBrick(brick) == 1) {
		brick.setPosition(positionImmortalBrick);
		positionImmortalBrick = Vector2f(rand(), rand());
	}
	ImmortalBrick.push_back(brick);
}


