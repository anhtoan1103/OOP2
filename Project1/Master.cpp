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
							ifstream file;
							file.open("highScore.txt");
							string name[20], score[20];
							int i = 0;
							while (!file.eof())
							{
								file >> name[i] >> score[i];
								i++;
							}
							file.close();
							Texture* A = new Texture;
							RectangleShape background;
							Font font_title; //font Tieu de
							Text title; //Tieu de	
							Font font;
							RectangleShape box[50];
							Text text[50];
							A->loadFromFile("background.jpg");
							background.setTexture(A);
							A->setSmooth(true);
							background.setPosition(Vector2f(0, 0));
							background.setSize(Vector2f(WIDTH, HEIGHT));
							RenderWindow window(VideoMode(WIDTH, HEIGHT), "Pong Game");
							font.loadFromFile("OCRAEXT.TTF");
							for (int j = 0; j < i; j++)
							{
							
							text[j].setFont(font);
							text[j].setPosition(425, 355+j*29);
							text[j].setCharacterSize(30);
							text[j].setString(name[j] + createString(10-name[j].length()) + score[j] + "\n");
							}
							window.draw(background);
							for (int j = 0; j < i; j++)
							{
								window.draw(box[j]);
								window.draw(text[j]);
							}
							window.display();
							
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
							}
							
							break;
						}
		
						case 2:
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