#include "InputManager.h"
#include <SDL.h>

bool InputManager::processEvents() {
	mouse[0] = 0;
	mouse[1] = 0;
	space = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			return true;
		case SDL_MOUSEBUTTONDOWN:
			mouse[0] = (event.button.button == SDL_BUTTON_LEFT ? 1 : 0);
			mouse[1] = (event.button.button == SDL_BUTTON_RIGHT ? 1 : 0);
			SDL_GetMouseState(mousepos, mousepos + 1);
			break;
		case SDL_KEYDOWN:
			space = (event.key.keysym.sym == SDLK_SPACE ? 1 : 0);
			break;
		}
	}

	const Uint8* kb = SDL_GetKeyboardState(NULL);
	SDL_memcpy(numberkeys, kb + SDL_SCANCODE_0, 10);
	SDL_memcpy(alphakeys, kb + SDL_SCANCODE_A, 26);
	//space = kb[SDL_SCANCODE_SPACE];
	//enter = kb[SDL_SCANCODE_RETURN];
	return false;
}