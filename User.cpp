#include "User.h"
using namespace std;

User::User() {}

User::User(const string& username) : username(username) {}

string User::getUsername() const { return username; }
string User::getPassword() const { return password; }
string User::getBio() const { return bio; }

const vector<string>& User::getFollowers() const { return followers; }
const vector<string>& User::getFollowing() const { return following; }
const vector<string>& User::getBlocked() const { return blocked; }
const vector<int>& User::getPosts() const { return posts; }

void User::setPassword(const string& p) { password = p; }
void User::setBio(const string& b) { bio = b; }

void User::addFollower(const string& u) { followers.push_back(u); }
void User::addFollowing(const string& u) { following.push_back(u); }

bool User::removeFollower(const string& u) {
    for (size_t i = 0; i < followers.size(); i++) {
        if (followers[i] == u) {
            followers.erase(followers.begin() + i);
            return true;
        }
    }
    return false;
}

bool User::removeFollowing(const string& u) {
    for (size_t i = 0; i < following.size(); i++) {
        if (following[i] == u) {
            following.erase(following.begin() + i);
            return true;
        }
    }
    return false;
}

bool User::isFollowing(const string& u) const {
    for (const auto& x : following) {
        if (x == u) return true;
    }
    return false;
}

void User::blockUser(const string& u) {
    for (const auto& x : blocked) if (x == u) return;
    blocked.push_back(u);
}

void User::unblockUser(const string& u) {
    for (size_t i = 0; i < blocked.size(); i++) {
        if (blocked[i] == u) {
            blocked.erase(blocked.begin() + i);
            return;
        }
    }
}

bool User::isBlocked(const string& u) const {
    for (const auto& x : blocked) if (x == u) return true;
    return false;
}

void User::addPost(int postId) {
    posts.push_back(postId);
}
