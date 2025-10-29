#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <stdio.h>
#include <memory>
#include <SDL_ttf.h>

#include "Window/Window.h"
#include "Network/HttpClient.h"
#include "HTML/HTMLParser.h"
#include "HTML/HTMLNode.h"
#include "Renderer/Renderer.h"

int main(int argc, char* argv[]) {
	SDL_Renderer* renderer = nullptr;
	SDL_Window* window = nullptr;

	//fuck error handling :)
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(1280, 720, 0, &window, &renderer);
	SDL_SetWindowResizable(window, SDL_TRUE);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	TTF_Init();

	HttpClient http;
	std::string url = "https://html.aze.cx/";

	HTMLParser parser;

	std::shared_ptr<HTMLNode> dom = parser.parse(http.get(url));

	http.~HttpClient();

	Window* browserWindow = new Window();
	
	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
			}
		}

		browserWindow->render(renderer, window, dom);

		SDL_Delay(16); 
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}