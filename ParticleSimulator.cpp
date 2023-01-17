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

	// Initializes SDL window and renderer
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = SDL_CreateWindow("Particle Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

	double deltaTime = 0;
	// Creates list of random particles with random properties
	vector<Particle> particles = vector<Particle>();
	/*for (int i = 0; i < 100; i++) {
		particles.push_back(Particle(rand() % 1280, rand() % 720, rand() % 20 - 10, rand() % 20 - 10, rand() % 10 + 1, rand() % 10 + 2, &deltaTime));
	}*/
	particles.push_back(Particle(600, 500, -1, 0, 5, 5, &deltaTime));
	particles.push_back(Particle(500, 501, 1, 0, 5, 5, &deltaTime));

	bool physicsLoop = true;
	bool running = true;
	while (running) {
		SDL_PumpEvents();

		if (input.processEvents()) {
			running = false;
		}

		// Draws the filled circles
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
		for (size_t i = 0; i < particles.size(); i++) {
			SDL_RenderFillCircle(renderer, (int)particles.at(i).x, (int)particles.at(i).y, (int)particles.at(i).size);
		}
		//SDL_Delay(10);

		// If spacebar is pressed, pause the physics loop
		if (input.space) {
			physicsLoop = !physicsLoop;
		}

		double FPS;
		Uint64 start = SDL_GetPerformanceCounter();
		if (physicsLoop == true) {
			for (size_t i = 0; i < particles.size(); i++) {
				particles.at(i).move();
				for (size_t j = i + 1; j < particles.size(); j++) {
					particles.at(i).collide(particles.at(j));
					particles.at(i).gravitate(particles.at(j));
				}
			}
			Uint64 end = SDL_GetPerformanceCounter();
			deltaTime = (end - start) / (double)SDL_GetPerformanceFrequency() * 1000.0f;
			FPS = 1 / deltaTime;
			cout << FPS << endl;
		}

		if (physicsLoop == false) {
			// left click adds a particle on the mouse position
			if (input.mouse[0]) {
				particles.push_back(Particle(input.mousepos[0], input.mousepos[1], 0, 0, rand() % 10 + 1, rand() % 10, &deltaTime));
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
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
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