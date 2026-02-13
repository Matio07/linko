#include "Post.h"
#include <ctime>
using namespace std;

Post::Post() {}

Post::Post(int id, const string& content, const string& author)
    : id(id), content(content), author(author), likeCount(0) {
    postTime = time(nullptr);
}

int Post::getId() const { return id; }
const string& Post::getContent() const { return content; }
const string& Post::getAuthor() const { return author; }
int Post::getLikeCount() const { return likeCount; }
long Post::getPostTime() const { return postTime; }
const vector<Comment>& Post::getComments() const { return comments; }

void Post::like() { likeCount++; }

void Post::addComment(const Comment& comment) { comments.push_back(comment); }

void Post::setLikeCount(int likes) { likeCount = likes; }
void Post::setPostTime(long t) { postTime = t; }

void Post::setContent(const string& newContent) { content = newContent; }
