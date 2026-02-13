#ifndef FEED_H
#define FEED_H

#include <string>
#include <vector>
#include "Network.h"

class Feed {
private:
    Network* network;

public:
    Feed(Network* n);
    std::vector<Post> generateFeed(const std::string& username);
};

#endif
