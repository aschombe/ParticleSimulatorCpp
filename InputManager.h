#pragma once
#include <SDL.h>

class InputManager {
public:
	Uint8 alphakeys[26];
	Uint8 numberkeys[10];
	Uint8 space;
	Uint8 enter;
	Uint8 mouse[2];
	int mousepos[2];
	
	bool processEvents();
};