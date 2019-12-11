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
		score[1]++;
	if (temp.isMoveRight * vx > 0)
	{
		vy -= 0.1;
		if (vx > 0)
		{
			vx += 0.1;
		}
		else
		{
			vx -= 0.1;
		}
	}
	else
	{
		vy += 0.1;
		if (vx > 0)
		{
			vx += 0.1;
		}
		else
		{
			vx -= 0.1;
		}
	}
	
	

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
	vx = -vx;
}

void Ball::hitTopBrick()
{
	vy = -vy;
}

void Ball::hitBotBrick()
{
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
int Ball::move(int WIDTH, int HEIGHT,  Paddle paddle2, RenderWindow &window)
{
	for (int i = 0; i < Brick.size(); i++)
	{
		if (getPosition().intersects(Brick[i].getGlobalBounds()))
		{
			hitBotBrick();
			Brick.erase(Brick.begin() + i);
			for (int i = 0; i < Brick.size(); i++)
			{
				window.draw(Brick[i]);
			}
		}
	}
	
	if (getPosition().top < 0)
	{
		hitSides();
	}
	
	if (getPosition().left >WIDTH)
	{
		hitRight();
	}

	if (getPosition().left < 0) 
	{
		hitLeft();
	}
	if (getPosition().intersects(paddle2.getPosition()))
	{
		hitPaddle2(paddle2);
	}
	if (getPosition().height+getPosition().top> HEIGHT)
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
	cout << i << j << endl;
	file.open(file_name);
	int c=0, d=0;
	while (!file.eof())
	{
		file.getline(a, 250);
		
		for (c = 0; c < j; c++)
		{
			arr[c+d*j] = a[c];
			cout << arr[c + d *j] ;
		}
		cout << endl;
		d++;
	}
	file.close();

	

}

bool isExistBrick(Vector2f position, vector<RectangleShape> Brick)
{
	for (int i = 0; i < Brick.size(); i++) {
		if (Brick[i].getPosition() == position) {
			return 1;
		}
	}
	return 0;
}

void drawItem();