#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    std::string username;
    std::string password;
    std::string bio;

    std::vector<std::string> followers;
    std::vector<std::string> following;
    std::vector<std::string> blocked;
    std::vector<int> posts;

public:
    User();
    User(const std::string& username);

    const std::string& getUsername() const;

    const std::string& getBio() const;
    void setBio(const std::string& bio);

    void setPassword(const std::string& password);
    const std::string& getPassword() const;

    const std::vector<std::string>& getFollowers() const;
    const std::vector<std::string>& getFollowing() const;
    const std::vector<std::string>& getBlocked() const;
    const std::vector<int>& getPosts() const;

    void addFollower(const std::string& u);
    void addFollowing(const std::string& u);
    void blockUser(const std::string& u);
    void unblockUser(const std::string& u);
    void addPost(int postId);

    bool isBlocked(const std::string& u) const;
    bool isFollowing(const std::string& u) const;
};

#endif
