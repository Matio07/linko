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
    std::vector<Comment> comments;

public:
    Post();
    Post(int id, const std::string& content, const std::string& author);

    int getId() const;
    std::string getContent() const;
    std::string getAuthor() const;

    int getLikeCount() const;
    long getPostTime() const;

    const std::vector<Comment>& getComments() const;

    void setContent(const std::string& c);
    void like();

    void addComment(const Comment& c);

    void setLikeCount(int c);
    void setPostTime(long t);
};

#endif
