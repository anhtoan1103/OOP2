#include "StringNamePlayer.h"

int WIDTH = 1000;
int HEIGHT = 800;

void StringNamePlayer::setTheButtonPlay()
{
	button.setButton("PLAY NOW", { 170,70 }, 30, Color::White, Color::Black);
	button.setFont(font);
	button.setPosition({ 750, 50 });
}


void StringNamePlayer::setTheTextBoxOnePlayer()
{
	box.setSize(Vector2f(400, 50));
	box.setPosition(Vector2f(400, 380));

	text.setString("Player: ");
	text.setFont(font);
	text.setPosition(Vector2f(200, 380));
	text.setCharacterSize(40);

	font.loadFromFile("OCRAEXT.TTF");

	textbox.setTextBox(35, Color::Black, true);
	textbox.setFont(font);
	textbox.setLimit(true, 15);
	textbox.setPosition(Vector2f(400, 380));
}

string StringNamePlayer::fillNameOnePlayer()
{
	string kq;
	texture.loadFromFile("background.jpg", IntRect(0, 0, 1000, 800));
	texture.setSmooth(true);
	RectangleShape background;
	background.setTexture(&texture);
	background.setSize(Vector2f(1000, 800));

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
				break;
			case Event::MouseButtonPressed:
				if (button.isMouseOver(window2))
				{
					window2.close();
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
		window2.display();
	}
	kq = textbox.getText();
	return kq;
}