#include "Comment.h"
using namespace std;

Comment::Comment() {}

Comment::Comment(const string& author, const string& text)
    : author(author), text(text) {}

string Comment::getAuthor() const { return author; }
string Comment::getText() const { return text; }
