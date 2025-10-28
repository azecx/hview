#include "HTMLParser.h"
#include <stack>
#include <cctype>
#include <algorithm>
#include <iostream>

std::vector<std::pair<std::string, std::string>> parseAttributes(const std::string& tag) {
    std::vector<std::pair<std::string, std::string>> attrs;
    size_t i = 0;

    while (i < tag.size()) {
        // skip spaces
        while (i < tag.size() && isspace(tag[i])) i++;

        size_t name_start = i;
        while (i < tag.size() && tag[i] != '=' && !isspace(tag[i])) i++;
        std::string name = tag.substr(name_start, i - name_start);

        //skip whitespace before '='
        while (i < tag.size() && isspace(tag[i])) i++;

        if (i < tag.size() && tag[i] == '=') {
            i++; //skip '='

            // skip skip skip skip skip holy shit we're skipping a lot
            while (i < tag.size() && isspace(tag[i])) i++;

            std::string value;
            if (i < tag.size() && (tag[i] == '"' || tag[i] == '\'' || tag[i] == '`')) {
                char quote = tag[i++];
                size_t value_start = i;
                size_t value_end = tag.find(quote, i);
                if (value_end == std::string::npos) value_end = tag.size();
                value = tag.substr(value_start, value_end - value_start);
                i = value_end + 1;
            }
            else {
                size_t value_start = i;
                while (i < tag.size() && !isspace(tag[i])) i++;
                value = tag.substr(value_start, i - value_start);
            }

            attrs.push_back({ name, value });
        }
        else if (!name.empty()) {
            attrs.push_back({ name, "" });
        }
    }

    return attrs;
}

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

                // extract tag name and attributes
                size_t space_pos = tag.find(' ');
                std::string tagName = (space_pos == std::string::npos) ? tag : tag.substr(0, space_pos);
                std::vector<std::pair<std::string, std::string>> attrs;
                if (space_pos != std::string::npos) {
                    std::string attrString = tag.substr(space_pos + 1);
                    attrs = parseAttributes(attrString);
                }

                auto node = HTMLNode::createElement(tagName);
                node->attributes = attrs;
                stack.top()->children.push_back(node);
                node->parent = stack.top();

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
