#include "Master.h"
#include "fstream"
string createString(int n)
{
	string s = "";
	for (int i = 0; i < n; i++)
	{
		s = s + " ";
	}
	return s;
}
void Master::processGame()
{
	RenderWindow beginWindow(VideoMode(WIDTH, HEIGHT), "Pong Game"); 

	StarMenu begin;

	Event event;
	Button button;
	if (beginWindow.isOpen())
	{
		while (beginWindow.isOpen())
		{
			while (beginWindow.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					beginWindow.close();
				}
				else if (event.type == Event::KeyReleased)
				{
					if (event.key.code == Keyboard::Up)
					{
						begin.moveUp();
					}
					else if (event.key.code == Keyboard::Down)
					{
						begin.moveDown();
					}
					else if (event.key.code == Keyboard::Enter)
					{
						switch (begin.getChoose())
						{
						case 0:
						{
							beginWindow.close();
							StringNamePlayer player;
							int flag = 0;
							string kq = player.fillNameOnePlayer(flag);
							if (flag)
							{
								WindowPlayGame playGame;
								vector <string> winer = playGame.playGameOnePlayer(kq);
								playGame.Winer(winer);
							}
							break;
						}
						case 1: 
						{
							beginWindow.close();
							WindowPlayGame playGame;
							vector <string> winer = playGame.autoPlay();
							playGame.Winer(winer);
							break;
						}
						case 2:
						{

							beginWindow.close();
							ifstream file;
							file.open("highScore.txt");
							string name[100];
							int point[100];
							int index = 0;
							while (!file.eof())
							{
								file >> name[index] >> point[index];
								index++;
							}
							file.close();
							for (int i = 0; i < index - 1; i++) {
								for (int j = i + 1; j < index; j++) {
									if (point[j] > point[i]) {
										swap(point[i], point[j]);
										swap(name[i], name[j]);
									}
								}
							}
							Texture* A = new Texture;
							Font font_title; //font Tieu de
							Text title; //Tieu de	
							Font font;
							Text text[200];
							RectangleShape background;

							A->loadFromFile("background.jpg");
							background.setTexture(A);
							A->setSmooth(true);
							background.setPosition(Vector2f(0, 0));
							background.setSize(Vector2f(WIDTH, HEIGHT));

							font.loadFromFile("OCRAEXT.TTF");
							title.setString("HIGHSCORE");
							title.setPosition(Vector2f(475, 80));
							title.setCharacterSize(100);
							title.setFont(font);

							RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong Game");
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
								window.draw(background);
								window.draw(title);
								for (int j = 0; j < index; j++)
								{
									text[j].setFont(font);
									text[j].setPosition(500, 255 + j * 60);
									text[j].setCharacterSize(30);
									text[j].setString(to_string(j + 1) + "st" + "       " +name[j] + 
										": " + to_string(point[j]) + "\n");
								}
								for (int j = 0; j < index; j++)
								{
									window.draw(text[j]);
								}
								window.display();
							}
							break;
						}
						case 3:
							beginWindow.close();
							break;
						}
					}
				}
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				beginWindow.close();
			}
			beginWindow.clear();
			begin.draw(beginWindow);
			beginWindow.display();
		}
	}
}