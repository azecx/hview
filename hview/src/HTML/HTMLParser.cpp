#include "HTMLParser.h"
#include <stack>
#include <cctype>

std::shared_ptr<HTMLNode> HTMLParser::parse(const std::string& html) {
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
                if (!stack.empty()) stack.pop();
                i = (end == std::string::npos) ? html.size() : end + 1;
            }
            // opening tag
            else {
                i++;
                size_t end = html.find('>', i);
                if (end == std::string::npos) end = html.size();
                std::string tag = html.substr(i, end - i);

                // remove trailing spaces or slashes
                while (!tag.empty() && (isspace(tag.back()) || tag.back() == '/'))
                    tag.pop_back();

                auto node = HTMLNode::createElement(tag);
                stack.top()->children.push_back(node);
                node->parent = stack.top();
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
