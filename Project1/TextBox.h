#pragma once
#define DELETEKEY 8
#define ENTERKEY 13
#define ESCAPEKEY 27
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
using namespace std;
#include <sstream>


class TextBox
{
private:

	int limit = 0;
	Text textBox; //Chuoi hoan chinh ma nguoi dung nhap vao
	ostringstream text;  //Chuoi nguoi dung nhap vao co the xoa/sua
	bool isSelected = false; //Bien kiem tra o da duoc chon chua
	bool hasLimit = false; //Gioi han ki tu
	void inputLogic(int charTyped);
	void deleteLastChar();  //Xoa ki tu cuoi
public:
	void setTextBox(int size, Color color, bool sel);
	void setFont(Font& font);
	void setPosition(Vector2f pos);
	void setLimit(bool existLimit);
	void setLimit(bool existLimit, int lim);
											
	string getText(); 
	void draw(RenderWindow& window);
	void typedOn(Event input); 
	int getLimit();
};
