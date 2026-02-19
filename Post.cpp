#include "Post.h"
#include <ctime>
using namespace std;

static string normalizeLikedByString(string s) {
    if (s.empty()) return ";";
    if (s.front() != ';') s.insert(s.begin(), ';');
    if (s.back() != ';') s.push_back(';');
    return s;
}

Post::Post() : id(0), likeCount(0), postTime(0), likedBy(";") {}

Post::Post(int id, const string& content, const string& author)
    : id(id), content(content), author(author), likeCount(0), likedBy(";") {
    postTime = (long)time(nullptr);
}

int Post::getId() const { return id; }
string Post::getContent() const { return content; }
string Post::getAuthor() const { return author; }

int Post::getLikeCount() const { return likeCount; }
long Post::getPostTime() const { return postTime; }

const string& Post::getLikedByString() const { return likedBy; }

int Post::countLikesFromString() const {
    int count = 0;
    string cur;
    for (size_t i = 0; i < likedBy.size(); i++) {
        char c = likedBy[i];
        if (c == ';') {
            if (!cur.empty()) {
                count++;
                cur.clear();
            }
        } else {
            cur.push_back(c);
        }
    }
    return count;
}

bool Post::hasLiked(const string& username) const {
    if (username.empty()) return false;
    string needle = ";" + username + ";";
    return likedBy.find(needle) != string::npos;
}

bool Post::likeBy(const string& username) {
    if (username.empty()) return false;
    if (hasLiked(username)) return false;

    likedBy += username;
    likedBy.push_back(';');
    likeCount++;
    return true;
}

const vector<Comment>& Post::getComments() const { return comments; }

void Post::setContent(const string& c) { content = c; }

void Post::like() { likeCount++; }

void Post::addComment(const Comment& c) { comments.push_back(c); }

void Post::setLikeCount(int c) { likeCount = c; }
void Post::setPostTime(long t) { postTime = t; }

void Post::setLikedByString(const string& s) {
    likedBy = normalizeLikedByString(s);
    likeCount = countLikesFromString();
}
