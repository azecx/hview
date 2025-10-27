#include "Window.h"
#include <iostream>

void Window::render(SDL_Renderer* renderer, SDL_Window* window) {
	if (!renderer || !window) {
		std::cerr << "Renderer or Window is null!" << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	SDL_Rect rect = { 10, 15, 10, 15 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &rect);

	SDL_RenderPresent(renderer);
}