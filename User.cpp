#include "User.h"

User::User() {}

User::User(const std::string& username) : username(username) {}

const std::string& User::getUsername() const { return username; }

const std::string& User::getBio() const { return bio; }
void User::setBio(const std::string& b) { bio = b; }

void User::setPassword(const std::string& p) { password = p; }
const std::string& User::getPassword() const { return password; }

const std::vector<std::string>& User::getFollowers() const { return followers; }
const std::vector<std::string>& User::getFollowing() const { return following; }
const std::vector<std::string>& User::getBlocked() const { return blocked; }
const std::vector<int>& User::getPosts() const { return posts; }

void User::addFollower(const std::string& u) { followers.push_back(u); }
void User::addFollowing(const std::string& u) { following.push_back(u); }

void User::blockUser(const std::string& u) { blocked.push_back(u); }

void User::unblockUser(const std::string& u) {
    for (size_t i = 0; i < blocked.size(); i++) {
        if (blocked[i] == u) {
            blocked.erase(blocked.begin() + i);
            break;
        }
    }
}

void User::addPost(int postId) { posts.push_back(postId); }

bool User::isBlocked(const std::string& u) const {
    for (const auto& b : blocked) {
        if (b == u) return true;
    }
    return false;
}

bool User::isFollowing(const std::string& u) const {
    for (const auto& f : following) {
        if (f == u) return true;
    }
    return false;
}
