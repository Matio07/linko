#ifndef POST_H
#define POST_H

#include <string>
#include <vector>
#include <ctime>
#include "Comment.h"

class Post {
private:
    int id{};
    std::string content;
    std::string author;
    int likeCount{};
    long postTime{};
    std::vector<Comment> comments;

public:
    Post();
    Post(int id, const std::string& content, const std::string& author);

    int getId() const;
    const std::string& getContent() const;
    const std::string& getAuthor() const;
    int getLikeCount() const;
    long getPostTime() const;
    const std::vector<Comment>& getComments() const;

    void like();
    void addComment(const Comment& comment);

    void setContent(const std::string& newContent);

    void setLikeCount(int likes);
    void setPostTime(long t);
};

#endif
