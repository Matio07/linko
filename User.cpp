#include "User.h"

using namespace std;

User::User() {}

User::User(const string& username) : username(username) {}

const string& User::getUsername() const { return username; }

const string& User::getBio() const { return bio; }
void User::setBio(const string& b) { bio = b; }

void User::setPassword(const string& p) { password = p; }
const string& User::getPassword() const { return password; }

const vector<string>& User::getFollowers() const { return followers; }
const vector<string>& User::getFollowing() const { return following; }
const vector<string>& User::getBlocked() const { return blocked; }
const vector<int>& User::getPosts() const { return posts; }

void User::addFollower(const string& u) { followers.push_back(u); }
void User::addFollowing(const string& u) { following.push_back(u); }

void User::blockUser(const string& u) { blocked.push_back(u); }

void User::unblockUser(const string& u) {
    for (size_t i = 0; i < blocked.size(); i++) {
        if (blocked[i] == u) {
            blocked.erase(blocked.begin() + i);
            break;
        }
    }
}

void User::addPost(int postId) { posts.push_back(postId); }

bool User::isBlocked(const string& u) const {
    for (const auto& b : blocked) {
        if (b == u) return true;
    }
    return false;
}

bool User::isFollowing(const string& u) const {
    for (const auto& f : following) {
        if (f == u) return true;
    }
    return false;
}
