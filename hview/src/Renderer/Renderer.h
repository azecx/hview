#pragma once
#include <memory>
#include <string>
#include "SDL.h"
#include "SDL_ttf.h"
#include "../HTML/HTMLNode.h"

class Renderer {
public:
    TTF_Font* font = nullptr;
    TTF_Font* boldFont = nullptr;
    TTF_Font* italicFont = nullptr;
    TTF_Font* boldItalicFont = nullptr;

    Renderer(int pxSize = 24);
    ~Renderer();

    struct TextStyle {
        bool bold = false;
        bool italic = false;
        bool none = false;
        bool link = false;
    };

    void renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int& x, int& y, TextStyle style);

private:
    void drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, TextStyle style);
    int measureTextWidth(TTF_Font* baseFont, const std::string& text, TextStyle style);
};
