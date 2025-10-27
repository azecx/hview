#pragma once
#include <memory>
#include "SDL.h"
#include "../HTML/HTMLNode.h"
#include "SDL_ttf.h"
#include "stdio.h"
#include <iostream>


class Renderer {
public:
    TTF_Font* font;

    Renderer() {
        font = TTF_OpenFont("./assets/font/UbuntuMono.ttf", 24); 
        if (!font) {
            std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        }
    }

    ~Renderer() {
        if (font) TTF_CloseFont(font);
    }

    struct TextStyle {
        bool bold = false;
        bool italic = false;
        bool none = false;
        bool link = false;
    };

    void renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int& x, int& y, TextStyle style);
    
private:
    void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, TextStyle style);
};
