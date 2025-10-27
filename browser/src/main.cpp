#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <stdio.h>

#include "Window/Window.h"
#include "Network/HttpClient.h"

int main(int argc, char* argv[]) {
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(640, 640, 0, &window, &renderer);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	Window* browserWindow = new Window();
	
	bool running = true;
	SDL_Event event;

	HttpClient http;
	std::cout << http.get("https://html.aze.cx/") << std::endl;
	http.~HttpClient();

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		browserWindow->render(renderer, window);

		SDL_Delay(16); 
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}