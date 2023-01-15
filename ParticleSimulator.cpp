#include <Windows.h>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <SDL.h>

#include "InputManager.h"
#include "Particle.h"
#include "Circle.h"
using namespace std;

int simulate() {
	InputManager input = InputManager();
	int height, width;
	height = 1280;
	width = 720;
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, 0, 0);
	
	vector<Particle> particles = vector<Particle>();
	/*for (int i = 0; i < 100; i++) {
		particles.push_back(Particle(rand() % 1280, rand() % 720, rand() % 20 - 10, rand() % 20 - 10, rand() % 10 + 1, rand() % 10 + 2));
	}*/
	particles.push_back(Particle(600, 500, -1, 0, 5, 5));
	particles.push_back(Particle(500, 501, 1, 0, 5, 5));
	

	bool physicsLoop = true;
	bool running = true;
	while (running) {
		SDL_PumpEvents();
		
		if (input.processEvents()) {
			running = false;
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		for (size_t i = 0; i < particles.size(); i++) {
			SDL_RenderFillCircle(renderer, (int)particles.at(i).x, (int)particles.at(i).y, (int)particles.at(i).size);
		}
		SDL_RenderPresent(renderer);
		SDL_Delay(10);

		
		if (input.space) {
			physicsLoop = !physicsLoop;
		}


		if (physicsLoop == true) {
			for (size_t i = 0; i < particles.size(); i++) { 
				for (size_t j = i+1; j < particles.size(); j++) {
					if (i == j) {
						continue;
					}
					particles.at(j).gravitate(particles.at(i));
					particles.at(j).collide(particles.at(i));
				}
			}
			for (size_t o = 0; o < particles.size(); o++) {
				particles.at(o).move();
			}
		}

		if (physicsLoop == false) {
			// left click adds a particle on the mouse position
			if (input.mouse[0]) {
				particles.push_back(Particle(input.mousepos[0], input.mousepos[1], 0, 0, rand() % 10 + 1, rand() % 10));
			}
			// right click removes the particle on the mouse position
			else if (input.mouse[1]) {
				for (size_t i = 0; i < particles.size(); i++) {
					if (abs(input.mousepos[0] - particles.at(i).x) < particles.at(i).size + 5 && abs(input.mousepos[1] - particles.at(i).y) < particles.at(i).size + 5) {
						particles.erase(particles.begin() + i);
					}
				}
			}
		}
	}

	SDL_VideoQuit();
	SDL_Quit();
	return 0;
}

int main(int argc, char* argv[]) {
	HWND windowHandle = GetConsoleWindow();
	ShowWindow(windowHandle, true);
	simulate();
	return 0;
}