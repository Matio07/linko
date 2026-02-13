#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment {
private:
    std::string author;
    std::string text;

public:
    Comment();
    Comment(const std::string& author, const std::string& text);

    std::string getAuthor() const;
    std::string getText() const;
};

#endif

