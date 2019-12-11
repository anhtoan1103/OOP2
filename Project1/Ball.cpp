#include "Ball.h"


Ball::Ball(float initX, float initY)
{
	position.x = initX;
	position.y = initY;
	ballShape.setRadius(10);
	ballShape.setPosition(position);
	ballShape.setFillColor(Color::Red);
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
	score[1]++;
	vx = -vx;
}

void Ball::hitTopBrick()
{
	vy = -vy;
}

void Ball::hitBotBrick()
{
	score[1]++;
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
				Brick.erase(Brick.begin() + i);
				for (int i = 0; i < Brick.size(); i++)
				{
					window.draw(Brick[i]);
				}
			}
			else
			{
				hitBotBrick();
				Brick.erase(Brick.begin() + i);
				for (int i = 0; i < Brick.size(); i++)
				{
					window.draw(Brick[i]);
				}
			}
		}
	}
	if (getPosition().intersects(Gift1.getGlobalBounds()))
	{

	}

	if (getPosition().top < 0)
	{
		hitSides();
	}

	if (getPosition().left > WIDTH)
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
	return score[1];
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
	Texture* gift1Texture = new Texture;
	Texture* gift2Texture = new Texture;
	Texture* gift3Texture = new Texture;
	gift1Texture->loadFromFile("fire.png");
	gift2Texture->loadFromFile("rock.png");
	gift3Texture->loadFromFile("fighting.png");

	Gift1.setTexture(gift1Texture);
	Gift2.setTexture(gift2Texture);
	Gift3.setTexture(gift3Texture);

	Gift1.setRadius(20);
	Gift2.setRadius(20);
	Gift3.setRadius(20);
}

void Ball::drawItem(int index, RenderWindow& window)
{
	if (index == 1)
	{
		window.draw(Gift1);
	}
	else if (index == 2)
	{
		window.draw(Gift2);
	}
	else
	{
		window.draw(Gift3);
	}
}

int Ball::drawItemOnMap(RenderWindow& window, vector<RectangleShape> Brick)
{
	while (!isExistBrick(Vector2f(40 * (rand() % 10 + 1), 20 * (rand() % 10 + 1)), Brick))
	{
		drawItem(1 + rand() % 3,window);
		return 1 + rand() % 3;
	}
}

