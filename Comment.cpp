#include "Comment.h"
using namespace std;

Comment::Comment() {}

Comment::Comment(const string& a, const string& t) : author(a), text(t) {}

const string& Comment::getAuthor() const { return author; }
const string& Comment::getText() const { return text; }
