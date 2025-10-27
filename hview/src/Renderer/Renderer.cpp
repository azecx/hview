#include "Renderer.h"
#include <iostream>
#include <stdio.h>
#include <string>

int lineHeight = 30;

//thanks stackoverflow.com
int measureTextWidth(TTF_Font* font, const std::string& text, Renderer::TextStyle style) {
    int w = 0, h = 0;

    TTF_Font* measureFont = font;

    int prevStyle = TTF_GetFontStyle(measureFont); //idk how necessary this is but eh whatever

    int newStyle = TTF_STYLE_NORMAL;
    if (style.bold) newStyle |= TTF_STYLE_BOLD;
    if (style.italic) newStyle |= TTF_STYLE_ITALIC;
    TTF_SetFontStyle(measureFont, newStyle);

    if (TTF_SizeText(font, text.c_str(), &w, &h) != 0) {
        std::cerr << "TTF_SizeText failed: " << TTF_GetError() << std::endl;
        return 0;
    }

    TTF_SetFontStyle(measureFont, prevStyle);

    return w;
}

void Renderer::renderNode(SDL_Renderer* renderer, std::shared_ptr<HTMLNode> node, int& x, int& y, Renderer::TextStyle style) {
    if (node->type == HTMLNode::Type::TEXT) {
        drawText(renderer, node->textContent, x, y, style);
        x += measureTextWidth(font, node->textContent, style);
    }
    else if (node->type == HTMLNode::Type::ELEMENT) {
        TextStyle newStyle = style;
        if (node->tagName == "b") newStyle.bold = true;
        if (node->tagName == "i") newStyle.italic = true;

        if (node->tagName == "p") {
            x = 10; // reset x at line start
            y += lineHeight;
        }

        for (auto& child : node->children) {
            renderNode(renderer, child, x, y, newStyle);
        }
    }
}



void Renderer::drawText(SDL_Renderer* renderer, const std::string& text, int x, int y, Renderer::TextStyle style) {
    TTF_Font* drawFont = font;

    int prevStyle = TTF_GetFontStyle(drawFont);

    int newStyle = TTF_STYLE_NORMAL;
    if (style.bold) newStyle |= TTF_STYLE_BOLD;
    if (style.italic) newStyle |= TTF_STYLE_ITALIC;
    TTF_SetFontStyle(drawFont, newStyle);

    SDL_Color color = { 0, 0, 0, 255 };
    SDL_Surface* surface = TTF_RenderText_Blended(drawFont, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = { x, y, 0, 0 };
    SDL_QueryTexture(texture, nullptr, nullptr, &dstRect.w, &dstRect.h);
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);

    TTF_SetFontStyle(drawFont, prevStyle);
}
