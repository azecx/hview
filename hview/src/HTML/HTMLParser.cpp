#include "HTMLParser.h"
#include <stack>
#include <cctype>
#include <algorithm>
#include <iostream>

std::shared_ptr<HTMLNode> HTMLParser::parse(const std::string& inputHTML) {
    std::string html = inputHTML;

    html.erase(std::remove_if(html.begin(), html.end(), [](char c) {
        return c == '\n' || c == '\r' || c == '\t';
        }), html.end());

    auto root = HTMLNode::createElement("root");
    std::stack<std::shared_ptr<HTMLNode>> stack;
    stack.push(root);

    size_t i = 0;
    while (i < html.size()) {
        if (html[i] == '<') {
            // closing tag
            if (i + 1 < html.size() && html[i + 1] == '/') {
                i += 2;
                size_t end = html.find('>', i);
                std::string tag = html.substr(i, end - i);

                if (!stack.empty() && stack.top()->tagName == tag)
                    stack.pop();

                i = (end == std::string::npos) ? html.size() : end + 1;
            }
            // opening tag
            else {
                i++;
                size_t end = html.find('>', i);
                if (end == std::string::npos) end = html.size();

                std::string tag = html.substr(i, end - i);

                // check if self-closing
                bool selfClosing = false;
                if (!tag.empty() && tag.back() == '/') {
                    selfClosing = true;
                    tag.pop_back(); 
                }

                // trim spaces
                while (!tag.empty() && isspace(tag.back()))
                    tag.pop_back();

                auto node = HTMLNode::createElement(tag);
                stack.top()->children.push_back(node);
                node->parent = stack.top();

                // only push if not self-closing
                if (!selfClosing)
                    stack.push(node);

                i = end + 1;
            }
        }
        // text node
        else {
            size_t end = html.find('<', i);
            if (end == std::string::npos) end = html.size();
            std::string text = html.substr(i, end - i);

            if (!text.empty()) {
                auto txtNode = HTMLNode::createText(text);
                stack.top()->children.push_back(txtNode);
                txtNode->parent = stack.top();
            }
            i = end;
        }
    }

    return root;
}
