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

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getBio() const;

    const std::vector<std::string>& getFollowers() const;
    const std::vector<std::string>& getFollowing() const;
    const std::vector<std::string>& getBlocked() const;
    const std::vector<int>& getPosts() const;

    void setPassword(const std::string& p);
    void setBio(const std::string& b);

    void addFollower(const std::string& u);
    void addFollowing(const std::string& u);

    bool removeFollower(const std::string& u);
    bool removeFollowing(const std::string& u);

    bool isFollowing(const std::string& u) const;

    void blockUser(const std::string& u);
    void unblockUser(const std::string& u);
    bool isBlocked(const std::string& u) const;

    void addPost(int postId);
};

#endif
