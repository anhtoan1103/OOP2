#include "StarMenu.h"

StarMenu::StarMenu()
{
	Texture * A = new Texture;
	A->loadFromFile("background.jpg");
	background.setTexture(A);
	A->setSmooth(true);
	background.setPosition(Vector2f(0, 0));
	background.setSize(Vector2f(1366, 768));


	font_title.loadFromFile("OCRAEXT.TTF");
	title.setCharacterSize(70);
	title.setString("Ping Pong!");
	title.setPosition(500, 80);
	title.setFont(font_title);

	font.loadFromFile("OCRAEXT.TTF");

	text[0].setFont(font);
	text[0].setPosition(625, 205);
	text[0].setCharacterSize(30);
	text[0].setString("> PLAY");

	text[1].setFont(font);
	text[1].setPosition(625, 283);
	text[1].setCharacterSize(30);
	text[1].setString("HIGH SCORES");

	text[2].setFont(font);
	text[2].setPosition(625, 365);
	text[2].setCharacterSize(30);
	text[2].setString("QUIT");

	

	selectItem = 0; 
}

void StarMenu::draw(RenderWindow& window)
{

	window.draw(background);
	window.draw(title);
	for (int i = 0; i < OBJECTS; i++)
	{
		window.draw(box[i]);
		window.draw(text[i]);
	}
}

void StarMenu::moveUp()
{
	if (selectItem - 1 >= 0)
	{
		string temp = text[selectItem].getString();
		temp.erase(0, 2);
		text[selectItem].setString(temp);
		selectItem--;
		temp = text[selectItem].getString();
		temp.insert(0, "> ");
		text[selectItem].setString(temp);
	}
}

void StarMenu::moveDown()
{
	if (selectItem + 1 < OBJECTS)
	{
		string temp = text[selectItem].getString();
		temp.erase(0, 2);
		text[selectItem].setString(temp);
		selectItem++;
		temp = text[selectItem].getString();
		temp.insert(0, "> ");
		text[selectItem].setString(temp);
	}
}

int StarMenu::getChoose()
{
	return selectItem;
}
