#ifndef POST_H
#define POST_H

#include <string>
#include <vector>
#include "Comment.h"

class Post {
private:
    int id;
    std::string content;
    std::string author;
    int likeCount;
    long postTime;

    std::string likedBy; // format: ;user1;user2;

    std::vector<Comment> comments;

    int countLikesFromString() const;

public:
    Post();
    Post(int id, const std::string& content, const std::string& author);

    int getId() const;
    std::string getContent() const;
    std::string getAuthor() const;

    int getLikeCount() const;
    long getPostTime() const;

    const std::string& getLikedByString() const;

    bool hasLiked(const std::string& username) const;
    bool likeBy(const std::string& username);

    const std::vector<Comment>& getComments() const;

    void setContent(const std::string& c);
    void like();
    void addComment(const Comment& c);

    void setLikeCount(int c);
    void setPostTime(long t);
    void setLikedByString(const std::string& s);
};

#endif
