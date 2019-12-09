#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;

class Button
{
private:
	RectangleShape button; //Hinh nut chu nhat
	Text text; //Chuoi
	int buttonWidth; //Do rong nut
	int buttonHeight; //Chieu cao nut
public:
	void setTextColor(Color color); 
	void setPosition(Vector2f point);
	void draw(RenderWindow& window);
	bool isMouseOver(RenderWindow& window); //Kiem tra xem con chuot co o vi tri cua nut hay khong
	void setButton(string buttonText, Vector2f buttonSize, int charSize, Color buttonColor, Color textColor); 
	void setFont(Font& font);
	void setBackColor(Color color);
};