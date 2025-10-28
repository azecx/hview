#pragma once
#include <string>
#include <vector>
#include <memory>

struct HTMLNode {
    enum class Type {
        ELEMENT,
        TEXT
    };

    Type type;
    std::string tagName;        
    std::string textContent;   

    std::vector<std::shared_ptr<HTMLNode>> children;
    std::weak_ptr<HTMLNode> parent;
    std::vector<std::pair<std::string, std::string>> attributes;

    static std::shared_ptr<HTMLNode> createElement(const std::string& tag);
    static std::shared_ptr<HTMLNode> createText(const std::string& text);
};
