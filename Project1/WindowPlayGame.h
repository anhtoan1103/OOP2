#pragma once
#include "Header.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class WindowPlayGame
{
private:
	int  WIDTH = 1366;
	int HEIGHT = 768;
	Font font_Score; 
	Text text[2];
	Font font_Speed;
	Text speed; 
	Text namePlayer[2]; 
	Font font_name; 
	int count;
public:


	vector <string> playGameOnePlayer(string name); 

	void Winer(vector <string> name);

};