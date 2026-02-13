#ifndef FEED_H
#define FEED_H

#include "Network.h"
#include <vector>

class Feed {
private:
    Network* network;

public:
    Feed(Network* network);
    std::vector<Post> generateFeed(const std::string& username);
};

#endif
