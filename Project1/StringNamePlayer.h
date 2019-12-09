#pragma once
#include "Header.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

#include "TextBox.h"
class TextBox;
class StringNamePlayer
{
private:
	RectangleShape box1; //Cho de nhap ten 1
	RectangleShape box2; //Cho de nhap ten 2
	Text text1; //Player1
	Text text2; //Player2
	TextBox textbox1; //Khung nhap ten 1
	TextBox textbox2;//Khung nhap ten 2
	RectangleShape box; 
	Text text;
	TextBox textbox;

	Button button; //Nut bam vao de bat dau choi
	Texture texture; 
	Font font;

public:

	void setTheButtonPlay();

	void setTheTextBoxTwoPlayer();

	vector <string> fillNameTwoPlayer();

	void setTheTextBoxOnePlayer();

	string fillNameOnePlayer();
};