#include "StringNamePlayer.h"

int WIDTH = 1366;
int HEIGHT = 768;

void StringNamePlayer::setTheButtonPlay()
{
	button.setButton("PLAY NOW", { 170,70 }, 30, Color::White, Color::Black);
	button.setFont(font);
	button.setPosition({ 1150, 50 });

	button2.setButton("BACK MENU", { 170, 70 }, 30, Color::White, Color::Black);
	button2.setFont(font);
	button2.setPosition({ 40, 55 });
}


void StringNamePlayer::setTheTextBoxOnePlayer()
{
	box.setSize(Vector2f(400, 50));
	box.setPosition(Vector2f(600, 380));

	text.setString("Player: ");
	text.setFont(font);
	text.setPosition(Vector2f(400, 380));
	text.setCharacterSize(40);

	font.loadFromFile("OCRAEXT.TTF");

	textbox.setTextBox(35, Color::Black, true);
	textbox.setFont(font);
	textbox.setLimit(true, 15);
	textbox.setPosition(Vector2f(600, 380));
}

string StringNamePlayer::fillNameOnePlayer(int &flag)
{
	string kq;
	texture.loadFromFile("background.jpg", IntRect(0, 0, WIDTH, HEIGHT));
	texture.setSmooth(true);
	RectangleShape background;
	background.setTexture(&texture);
	background.setSize(Vector2f(WIDTH, HEIGHT));

	setTheTextBoxOnePlayer();
	setTheButtonPlay();
	RenderWindow window2(VideoMode(WIDTH, HEIGHT), "Pong Game");
	while (window2.isOpen())
	{
		Event event;
		while (window2.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed:
				window2.close();
			case Event::TextEntered:
				if (textbox.getLimit() != 0)
				{
					textbox.typedOn(event);
				}
			case Event::MouseMoved:
				if (button.isMouseOver(window2))
				{
					button.setBackColor(Color::Magenta);
				}
				else
				{
					button.setBackColor(Color::White);
				}
				if (button2.isMouseOver(window2))
				{
					button2.setBackColor(Color::Magenta);
				}
				else
				{
					button2.setBackColor(Color::White);
				}
				break;
			case Event::MouseButtonPressed:
				if (button.isMouseOver(window2))
				{
					flag = 1;
					window2.close();
				}
				if (button2.isMouseOver(window2))
				{
					flag = 0;
					window2.close();
					Master newGamePlay;
					newGamePlay.processGame();
				}
				break;
			}
		}
		window2.clear();
		window2.draw(background);

		window2.draw(text);

		window2.draw(box);

		textbox.draw(window2);

		button.draw(window2);
		button2.draw(window2);
		window2.display();
	}
	kq = textbox.getText();
	return kq;
}