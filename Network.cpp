#include "Network.h"
using namespace std;

Network::Network() : nextPostId(1) {}

bool Network::userExists(const string& username) const {
    return users.find(username) != users.end();
}

bool Network::addUser(const string& username, const string& password) {
    if (userExists(username)) return false;

    User u(username);
    u.setPassword(password);
    users[username] = u;
    return true;
}

bool Network::checkPassword(const string& username, const string& password) const {
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second.getPassword() == password;
}

User* Network::getUser(const string& username) {
    auto it = users.find(username);
    if (it == users.end()) return nullptr;
    return &it->second;
}

const User* Network::getUserConst(const string& username) const {
    auto it = users.find(username);
    if (it == users.end()) return nullptr;
    return &it->second;
}

Post* Network::getPost(int id) {
    auto it = posts.find(id);
    if (it == posts.end()) return nullptr;
    return &it->second;
}

const Post* Network::getPostConst(int id) const {
    auto it = posts.find(id);
    if (it == posts.end()) return nullptr;
    return &it->second;
}

int Network::createPost(const string& username, const string& content) {
    if (!userExists(username)) return -1;

    Post p(nextPostId, content, username);
    posts[nextPostId] = p;

    User* u = getUser(username);
    if (u) u->addPost(nextPostId);

    nextPostId++;
    return nextPostId - 1;
}

bool Network::follow(const string& follower, const string& followee) {
    if (!userExists(follower) || !userExists(followee)) return false;

    User* f = getUser(follower);
    User* t = getUser(followee);

    if (!f || !t) return false;

    if (t->isBlocked(follower)) return false;

    f->addFollowing(followee);
    t->addFollower(follower);
    return true;
}

bool Network::likePost(int postId) {
    Post* p = getPost(postId);
    if (!p) return false;
    p->like();
    return true;
}

bool Network::commentPost(int postId, const string& author, const string& text) {
    Post* p = getPost(postId);
    if (!p) return false;
    p->addComment(Comment(author, text));
    return true;
}

bool Network::editPost(int postId, const string& editorUsername, const string& newContent) {
    auto it = posts.find(postId);
    if (it == posts.end()) return false;
    if (it->second.getAuthor() != editorUsername) return false;

    it->second.setContent(newContent);
    return true;
}

vector<string> Network::searchUser(const string& keyword) const {
    vector<string> results;
    for (const auto& pair : users) {
        if (pair.first.find(keyword) != string::npos) {
            results.push_back(pair.first);
        }
    }
    return results;
}

const map<int, Post>& Network::getAllPosts() const { return posts; }
const map<string, User>& Network::getAllUsers() const { return users; }

void Network::setNextPostId(int id) { nextPostId = id; }
int Network::getNextPostId() const { return nextPostId; }

void Network::addPostObject(const Post& post) {
    posts[post.getId()] = post;
    if (post.getId() >= nextPostId) nextPostId = post.getId() + 1;

    User* u = getUser(post.getAuthor());
    if (u) u->addPost(post.getId());
}

void Network::addUserObject(const User& user) {
    users[user.getUsername()] = user;
}
