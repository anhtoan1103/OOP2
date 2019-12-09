#pragma once 
#include <SFML/Graphics.hpp>
#include "Header.h"
using namespace std;
using namespace sf;

class Master
{
public:
	void processGame(); //Van hanh game
private:
	int WIDTH = 1000;
	int HEIGHT = 800;
};