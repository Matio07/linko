#include "Feed.h"
using namespace std;

Feed::Feed(Network* n) : network(n) {}

vector<Post> Feed::generateFeed(const string& username) {
    vector<Post> result;

    const User* u = network->getUserConst(username);
    if (!u) return result;

    const auto& following = u->getFollowing();
    const auto& allPosts = network->getAllPosts();

    for (const auto& pair : allPosts) {
        const Post& p = pair.second;
        if (u->isBlocked(p.getAuthor())) continue;

        if (p.getAuthor() == username) result.push_back(p);
        else {
            for (const auto& f : following) {
                if (p.getAuthor() == f) {
                    result.push_back(p);
                    break;
                }
            }
        }
    }

    for (size_t i = 0; i < result.size(); i++) {
        for (size_t j = 0; j + 1 < result.size(); j++) {
            if (result[j].getId() < result[j + 1].getId()) {
                Post tmp = result[j];
                result[j] = result[j + 1];
                result[j + 1] = tmp;
            }
        }
    }

    return result;
}
