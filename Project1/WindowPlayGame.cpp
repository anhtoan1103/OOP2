#include "WindowPlayGame.h"
#include <fstream>
#include "Ball.h"


//tra ve ten va so diem cua nguoi chien thang
vector <string> WindowPlayGame::playGameOnePlayer(string name)
{
	RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong Game");
	vector <string> kq;
	Ball ball(550, 400);

	Event event;
	Paddle paddle2(WIDTH/2-80 , HEIGHT-45);

	font_Score.loadFromFile("OCRAEXT.TTF");

	
	text[1].setCharacterSize(100);
	text[1].setPosition(550, 70);
	text[1].setFont(font_Score);

	font_Speed.loadFromFile("OCRAEXT.TTF");
	speed.setFont(font_Speed);
	speed.setPosition(768, 0);
	

	font_name.loadFromFile("OCRAEXT.ttf");


	namePlayer[1].setCharacterSize(20);
	namePlayer[1].setPosition(550, 45);
	namePlayer[1].setString(name);
	namePlayer[1].setFont(font_name);


	
	int tempWin = 0; //Note
	ball.defaultItem(Vector2f(150, 160), window);
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

		int Win = ball.move(WIDTH, HEIGHT, paddle2, window);
		
		
		ball.updatePosition();

		paddle2.autoMove(0, WIDTH, ball);
		paddle2.update();

		window.clear(Color::Black);

		/*if (ball.iPos == 0)
		{
			ball.defaultItem(Vector2f(150, 160), window);
		}*/
		ball.drawItem(window);
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

		if (ball.Brick.size() == 0) {
			window.close();
			kq.push_back("You are God !!!");
			kq.push_back("Score: " + scorePlayer2);
			fstream FileHighscore;
			FileHighscore.open("highscore.txt", ios::app);
			{
				FileHighscore << name << " " << scorePlayer2 << endl;
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
		FileHighscore << "Computer" << " " << ball.getScorePalyer2() << endl;
	}
	else {
		FileHighscore << name << " " << ball.getScorePalyer2() << endl;
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
	text[0].setPosition(550, 200);

	font.loadFromFile("OCRAEXT.ttf");
	text[1].setCharacterSize(100);
	text[1].setFont(font);
	text[1].setString(name[0]);
	text[1].setPosition(WIDTH / 2 - text[1].getLocalBounds().width / 2, 50);

	text[2].setCharacterSize(30);
	text[2].setFont(font);
	text[2].setString("Your " + name[1]); //score
	text[2].setPosition(600, 350);

	font.loadFromFile("OCRAEXT.ttf");
	text[3].setCharacterSize(30);
	text[3].setFont(font);
	text[3].setString("Enter to play a new game!");
	text[3].setPosition(520, 570);

	text[4].setCharacterSize(30);
	text[4].setFont(font);
	text[4].setString("Esc to given!");
	text[4].setPosition(600, 650);

	int HighScore = 0;
	/*fstream FileHighScore;
	FileHighScore.open("highscore.txt", ios::in);
	FileHighScore.close()*/
	Text A;
	A.setString("High score: 69");
	A.setFont(font);
	A.setPosition(600, 420);
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