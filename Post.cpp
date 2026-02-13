#include "Post.h"
#include <ctime>
using namespace std;

Post::Post() : id(0), likeCount(0), postTime(0) {}

Post::Post(int id, const string& content, const string& author)
    : id(id), content(content), author(author), likeCount(0) {
    postTime = (long)time(nullptr);
}

int Post::getId() const { return id; }
string Post::getContent() const { return content; }
string Post::getAuthor() const { return author; }

int Post::getLikeCount() const { return likeCount; }
long Post::getPostTime() const { return postTime; }

const vector<Comment>& Post::getComments() const { return comments; }

void Post::setContent(const string& c) { content = c; }
void Post::like() { likeCount++; }

void Post::addComment(const Comment& c) { comments.push_back(c); }

void Post::setLikeCount(int c) { likeCount = c; }
void Post::setPostTime(long t) { postTime = t; }
