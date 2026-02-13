#ifndef NETWORK_H
#define NETWORK_H

#include <map>
#include <string>
#include <vector>
#include "User.h"
#include "Post.h"

class Network {
private:
    std::map<std::string, User> users;
    std::map<int, Post> posts;
    int nextPostId;

public:
    Network();

    bool userExists(const std::string& username) const;
    bool addUser(const std::string& username, const std::string& password);
    bool checkPassword(const std::string& username, const std::string& password) const;

    User* getUser(const std::string& username);
    const User* getUserConst(const std::string& username) const;

    Post* getPost(int id);
    const Post* getPostConst(int id) const;

    int createPost(const std::string& username, const std::string& content);

    bool follow(const std::string& follower, const std::string& followee);
    bool unfollow(const std::string& follower, const std::string& followee);

    bool likePost(int postId);
    bool commentPost(int postId, const std::string& author, const std::string& text);

    bool editPost(int postId, const std::string& editorUsername, const std::string& newContent);

    std::vector<std::string> searchUser(const std::string& keyword) const;

    const std::map<int, Post>& getAllPosts() const;
    const std::map<std::string, User>& getAllUsers() const;

    void setNextPostId(int id);
    int getNextPostId() const;

    void addPostObject(const Post& post);
    void addUserObject(const User& user);
};

#endif
