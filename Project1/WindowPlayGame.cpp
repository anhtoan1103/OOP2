#include "WindowPlayGame.h"
#include <fstream>
#include "Ball.h"


//tra ve ten va so diem cua nguoi chien thang
vector <string> WindowPlayGame::playGameOnePlayer(string name)
{
	vector <string> kq;
	
	Ball ball(550, 400);

	Event event;


	Paddle paddle2(WIDTH/2-80 , HEIGHT-20);

	font_Score.loadFromFile("OCRAEXT.TTF");

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong Game");
	
	int i = 0, j = 0;
	ball.readFile(i, j, "2.txt");
	int count = 0;
	for (int a = 0; a < i; a++)
	{
		for (int b = 0; b < j; b++)

		{
			//RectangleShape brick;
			if ((int)arr[b + a * j] == 126)
			{
				RectangleShape brick;
				cout << "aa" << endl;
				ball.Brick.push_back(brick);
				ball.Brick[b + a * j].setPosition(Vector2f(50 + 42 * b, 60 + 22 * a));
				ball.Brick[b + a * j].setSize(Vector2f(40, 20));
				ball.Brick[b + a * j].setFillColor(Color(255, 0, 0));
				
				
			}
			else
			if ((int)arr[b + a * j] == 32)
			{
				RectangleShape brick;
				cout << "bb" << endl;

				ball.Brick.push_back(brick);
				ball.Brick[b + a * j].setPosition(Vector2f(50 + 92 * b, 60 + 22 * a));
				ball.Brick[b + a * j].setSize(Vector2f(90, 20));
				ball.Brick[b + a * j].setFillColor(Color(0, 0, 0));
				count++;
			}
			else
			if ((int)arr[b + a * j] == 45)
			{
				RectangleShape brick;
				cout << "cc" << endl;

				ball.Brick.push_back(brick);
				ball.Brick[b + a * j].setPosition(Vector2f(50 + 92 * b, 60 + 22 * a));
				ball.Brick[b + a * j].setSize(Vector2f(90, 20));
				ball.Brick[b + a * j].setFillColor(Color(0, 155, 0));
			}
			else
			{
				RectangleShape brick;
				cout << "dd" << endl;
				cout << (int)arr[b + a * j] << endl;
				ball.Brick.push_back(brick);
				ball.Brick[b + a * j].setPosition(Vector2f(50 + 92 * j, 60 + 22 * i));
				ball.Brick[b + a * j].setSize(Vector2f(90, 20));
				ball.Brick[b + a * j].setFillColor(Color(255, 0, 0));
			}
		}
	}

	text[1].setCharacterSize(100);
	text[1].setPosition(550, 70);
	text[1].setFont(font_Score);

	font_Speed.loadFromFile("OCRAEXT.TTF");
	speed.setFont(font_Speed);
	speed.setPosition(800, 0);
	

	font_name.loadFromFile("OCRAEXT.ttf");


	namePlayer[1].setCharacterSize(20);
	namePlayer[1].setPosition(550, 45);
	namePlayer[1].setString(name);
	namePlayer[1].setFont(font_name);


	int max_score = 0; //Note
	int tempWin = 0; //Note
	while (window.isOpen())
	{

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close(); //neu bam dau tat tren man hinh thi cua so tat
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			// move right paddle
			paddle2.moveRight(WIDTH);
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			// move left paddle
			paddle2.moveLeft(0);
			
		}
		else if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			//khi co ai do nhan phim ESC thi tat man hinh
			window.close();
		}

		//lay diem cua nguoi choi
		int score2 = ball.getScorePalyer2();

		string scorePlayer2 = to_string(score2);

		text[1].setString(scorePlayer2);

		string Speed = to_string(int(fabs(ball.getvx()) * 100) % 100);
		speed.setString("SPEED: " + Speed + "%");

		int Win = ball.move(WIDTH, HEIGHT, paddle2,window);
		
		ball.updatePosition();

		//paddle2.autoMove(0, 1000, ball);
		paddle2.update();

		window.clear(Color::Black);

		window.draw(text[1]);

		window.draw(paddle2.getShape());

		window.draw(namePlayer[1]);

		window.draw(speed);
		for (int i = 0; i < ball.Brick.size(); i++)
		{
		window.draw(ball.Brick[i]);
		}
		window.draw(ball.getShape());

		window.display();

		if (ball.Brick.size() == count) {
			window.close();
			kq.push_back("You are God !!!");
			kq.push_back("Score: " + scorePlayer2);
			fstream FileHighscore;
			FileHighscore.open("highscore.txt", ios::app);
			{
				FileHighscore << name << " " << max_score << endl;
			}
			FileHighscore.close();
			return kq;
		}

		if (Win == 1)
		{
			window.close();
			kq.push_back("Beat the GOD?");

			kq.push_back("Score: " + scorePlayer2);
		}
		else if (Win == 2)
		{
			window.close();
			kq.push_back(name);
			kq.push_back("Score: " + scorePlayer2);
		}
	}
	
	fstream FileHighscore;
	FileHighscore.open("highscore.txt", ios::app);
	if (tempWin == 1) {
		FileHighscore << "Computer" << " " << max_score << endl;
	}
	else {
		FileHighscore << name << " " << max_score << endl;
	}
	FileHighscore.close();
	return kq;
}

//hien thi man hinh ket thuc game va in ten, diem cua nguoi chien thang
void WindowPlayGame::Winer(vector <string> name)
{
	Font font;
	font.loadFromFile("OCRAEXT.TTF");

	Text text[5];

	text[0].setCharacterSize(50);
	text[0].setFont(font);
	text[0].setString("Win the game");
	text[0].setPosition(350, 200);

	font.loadFromFile("OCRAEXT.ttf");
	text[1].setCharacterSize(100);
	text[1].setFont(font);
	text[1].setString(name[0]);
	text[1].setPosition(WIDTH / 2 - text[1].getLocalBounds().width / 2, 50);

	text[2].setCharacterSize(30);
	text[2].setFont(font);
	text[2].setString("Your " + name[1]); //score
	text[2].setPosition(400, 350);

	font.loadFromFile("OCRAEXT.ttf");
	text[3].setCharacterSize(30);
	text[3].setFont(font);
	text[3].setString("Enter to play a new game!");
	text[3].setPosition(320, 570);

	text[4].setCharacterSize(30);
	text[4].setFont(font);
	text[4].setString("Esc to given!");
	text[4].setPosition(400, 650);

	int HighScore = 0;
	/*fstream FileHighScore;
	FileHighScore.open("highscore.txt", ios::in);
	FileHighScore.close()*/
	Text A;
	A.setString("High score: 69");
	A.setFont(font);
	A.setPosition(400, 420);
	A.setFillColor(Color::White);

	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong Game");

	Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			if (event.type == Event::KeyReleased)
			{
				switch (event.key.code)
				{
				case Keyboard::Escape:
				{
					window.close();
					break;
				}
				case Keyboard::Return:
				{
					window.close();
					Master starGame;
					starGame.processGame();
				}
				}
			}
		}
		window.clear(Color::Black);
		window.draw(A);
		for (int i = 0; i < 5; i++)
		{
			window.draw(text[i]);
		}
		window.display();
	}
}