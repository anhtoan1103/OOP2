#pragma once
#define SFML_NO_DEPRECATED_WARNINGS
#include <SFML/Graphics.hpp>
#include "Header.h"
using namespace sf;
#define OBJECTS 3 

class StarMenu
{
private:
	int selectItem; //Lua chon dang duoc chon
	Font font; 
	RectangleShape box[OBJECTS]; 
	Text text[OBJECTS]; //3 lua chon de choi
	Text title; //Tieu de
	Font font_title; //font Tieu de
	RectangleShape background; //Hinh nen
public:
	StarMenu(); 

	void draw(RenderWindow& window);

	void moveUp();

	void moveDown();

	int getChoose();

};
