#include "Button.h"

void Button::setButton(string buttonText, Vector2f buttonSize, int charSize, Color buttonColor, Color textColor)
{
	button.setSize(buttonSize);
	button.setFillColor(buttonColor);

	buttonWidth = buttonSize.x;
	buttonHeight = buttonSize.y;

	text.setString(buttonText);
	text.setCharacterSize(charSize);
	text.setFillColor(textColor);
}

void Button::setBackColor(Color color)
{
	button.setFillColor(color);
}

void Button::setTextColor(Color color)
{
	text.setFillColor(color);
}

void Button::setPosition(Vector2f point)
{
	button.setPosition(point);
	float xPos = (point.x + buttonWidth / 2) - (text.getLocalBounds().width / 2);
	float yPos = (point.y + buttonHeight / 2.2) - (text.getLocalBounds().height / 2);
	text.setPosition(xPos, yPos);
}

void Button::draw(RenderWindow& window)
{
	window.draw(button);
	window.draw(text);
}

bool Button::isMouseOver(RenderWindow& window)
{
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;
	int buttonPosX = button.getPosition().x;
	int buttonPosY = button.getPosition().y;

	int buttonxPosWidth = button.getPosition().x + buttonWidth;
	int buttonyPosHeight = button.getPosition().y + buttonHeight;

	if (mouseX < buttonxPosWidth && mouseX > buttonPosX && mouseY < buttonyPosHeight && mouseY > buttonPosY)
	{
		return true;
	}
	return false;
}

void Button::setFont(Font& font)
{
	text.setFont(font);
}

