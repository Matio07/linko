#include <iostream>
#include <limits>
#include <string>
#include <map>
#include <vector>

#include "../core/Network.h"
#include "../core/AuthManager.h"
#include "../core/FileManager.h"
#include "../core/Feed.h"

using namespace std;

static void eatLine() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

static string readRestOfLineTrim() {
    string s;
    getline(cin, s);
    if (!s.empty() && s[0] == ' ') s.erase(0, 1);
    return s;
}

static bool requireLogin(const AuthManager& auth) {
    if (!auth.isLoggedIn()) {
        cout << "You must login first\n";
        return false;
    }
    return true;
}

static void printHelp() {
    cout
        << "Commands:\n"
        << "  help\n"
        << "  register <u> <p>\n"
        << "  login <u> <p>\n"
        << "  logout\n"
        << "  post <text...>\n"
        << "  editpost <id> <new text...>\n"
        << "  follow <username>\n"
        << "  unfollow <username>\n"
        << "  like <postId>\n"
        << "  comment <postId> <text...>\n"
        << "  feed\n"
        << "  profile <username>\n"
        << "  block <username>\n"
        << "  unblock <username>\n"
        << "  search <keyword>\n"
        << "  save\n"
        << "  exit\n";
}

static void printPostNice(const Post& p) {
    cout << "[Post ID: " << p.getId() << "]   Likes: " << p.getLikeCount() << "\n";
    cout << p.getContent() << "\n";

    const auto& cs = p.getComments();
    if (!cs.empty()) {
        cout << "\n  Comments:\n";
        for (const auto& c : cs) {
            cout << "    - " << c.getAuthor() << " : " << c.getText() << "\n";
        }
    }
    cout << "\n------------------------------\n";
}

int main() {
    Network network;
    FileManager::load(&network);

    AuthManager auth(&network);
    Feed feed(&network);

    map<string, vector<int>> likedHistory;

    string cmd;
    printHelp();

    while (true) {
        cout << "> ";
        if (!(cin >> cmd)) break;

        if (cmd == "help") {
            eatLine();
            printHelp();
        }

        else if (cmd == "register") {
            string u, p;
            cin >> u >> p;
            eatLine();

            if (auth.registerUser(u, p)) cout << "Registered\n";
            else cout << "User already exists\n";
        }

        else if (cmd == "login") {
            string u, p;
            cin >> u >> p;
            eatLine();

            if (auth.login(u, p)) cout << "Logged in\n";
            else cout << "Wrong\n";
        }

        else if (cmd == "logout") {
            eatLine();
            auth.logout();
            cout << "Logged out\n";
        }

        else if (cmd == "post") {
            if (!requireLogin(auth)) { eatLine(); continue; }
            string content = readRestOfLineTrim();
            int id = network.createPost(auth.getCurrentUser(), content);
            if (id == -1) cout << "Author not found\n";
            else cout << "Posted id=" << id << "\n";
        }

        else if (cmd == "editpost") {
            if (!requireLogin(auth)) { eatLine(); continue; }

            int id;
            cin >> id;
            string newContent = readRestOfLineTrim();

            bool ok = network.editPost(id, auth.getCurrentUser(), newContent);
            if (ok) cout << "Edited\n";
            else cout << "Cannot edit (not found or not author)\n";
        }

        else if (cmd == "follow") {
            if (!requireLogin(auth)) { string dummy; cin >> dummy; eatLine(); continue; }

            string target;
            cin >> target;
            eatLine();

            bool ok = network.follow(auth.getCurrentUser(), target);
            if (ok) cout << "Followed\n";
            else cout << "Cannot follow\n";
        }

        else if (cmd == "unfollow") {
            if (!requireLogin(auth)) { string dummy; cin >> dummy; eatLine(); continue; }

            string target;
            cin >> target;
            eatLine();

            bool ok = network.unfollow(auth.getCurrentUser(), target);
            if (ok) cout << "Unfollowed\n";
            else cout << "Cannot unfollow\n";
        }

        else if (cmd == "like") {
            if (!requireLogin(auth)) { int dummy; cin >> dummy; eatLine(); continue; }

            int postId;
            cin >> postId;
            eatLine();

            const Post* p = network.getPostConst(postId);
            if (!p) { cout << "Post not found\n"; continue; }

            const string me = auth.getCurrentUser();
            const string owner = p->getAuthor();

            const User* meUser = network.getUserConst(me);
            const User* ownerUser = network.getUserConst(owner);

            if (meUser && meUser->isBlocked(owner)) { cout << "Blocked\n"; continue; }
            if (ownerUser && ownerUser->isBlocked(me)) { cout << "Blocked\n"; continue; }

            auto& v = likedHistory[me];
            bool already = false;
            for (int x : v) if (x == postId) { already = true; break; }
            if (already) { cout << "You already liked this post\n"; continue; }

            bool ok = network.likePost(postId);
            if (ok) { v.push_back(postId); cout << "Liked\n"; }
            else cout << "Cannot like\n";
        }

        else if (cmd == "comment") {
            if (!requireLogin(auth)) { int dummy; cin >> dummy; eatLine(); continue; }

            int postId;
            cin >> postId;
            string text = readRestOfLineTrim();

            const Post* p = network.getPostConst(postId);
            if (!p) { cout << "Post not found\n"; continue; }

            const string me = auth.getCurrentUser();
            const string owner = p->getAuthor();

            const User* meUser = network.getUserConst(me);
            const User* ownerUser = network.getUserConst(owner);

            if (meUser && meUser->isBlocked(owner)) { cout << "Blocked\n"; continue; }
            if (ownerUser && ownerUser->isBlocked(me)) { cout << "Blocked\n"; continue; }

            bool ok = network.commentPost(postId, me, text);
            if (ok) cout << "Commented\n";
            else cout << "Cannot comment\n";
        }

        else if (cmd == "feed") {
            eatLine();
            if (!requireLogin(auth)) continue;

            auto posts = feed.generateFeed(auth.getCurrentUser());
            if (posts.empty()) cout << "No posts\n";
            else {
                cout << "\n------------------------------\n";
                cout << "             FEED\n";
                cout << "------------------------------\n";
                for (const auto& x : posts) printPostNice(x);
            }
        }

        else if (cmd == "profile") {
            string name;
            cin >> name;
            eatLine();

            const User* u = network.getUserConst(name);
            if (!u) { cout << "User not found\n"; continue; }

            cout << "\n==============================\n";
            cout << "        PROFILE VIEW\n";
            cout << "==============================\n\n";

            cout << "Username : " << u->getUsername() << "\n";
            cout << "Bio      : " << u->getBio() << "\n\n";

            cout << "Followers (" << u->getFollowers().size() << ")\n";
            if (u->getFollowers().empty()) cout << "  (none)\n";
            else for (const auto& f : u->getFollowers()) cout << "  - " << f << "\n";

            cout << "\nFollowing (" << u->getFollowing().size() << ")\n";
            if (u->getFollowing().empty()) cout << "  (none)\n";
            else for (const auto& f : u->getFollowing()) cout << "  - " << f << "\n";

            cout << "\n------------------------------\n";
            cout << "Posts\n";
            cout << "------------------------------\n\n";

            vector<Post> userPosts;
            for (const auto& pair : network.getAllPosts()) {
                const Post& p = pair.second;
                if (p.getAuthor() == name) userPosts.push_back(p);
            }

            for (size_t i = 0; i < userPosts.size(); i++) {
                for (size_t j = 0; j + 1 < userPosts.size(); j++) {
                    if (userPosts[j].getId() < userPosts[j + 1].getId()) {
                        Post tmp = userPosts[j];
                        userPosts[j] = userPosts[j + 1];
                        userPosts[j + 1] = tmp;
                    }
                }
            }

            if (userPosts.empty()) cout << "No posts\n\n";
            else for (const auto& p : userPosts) printPostNice(p);
        }

        else if (cmd == "block") {
            if (!requireLogin(auth)) { string dummy; cin >> dummy; eatLine(); continue; }

            string target;
            cin >> target;
            eatLine();

            User* me = network.getUser(auth.getCurrentUser());
            if (!me) { cout << "Current user not found\n"; continue; }

            me->blockUser(target);
            network.unfollow(auth.getCurrentUser(), target);
            network.unfollow(target, auth.getCurrentUser());
            cout << "Blocked\n";
        }

        else if (cmd == "unblock") {
            if (!requireLogin(auth)) { string dummy; cin >> dummy; eatLine(); continue; }

            string target;
            cin >> target;
            eatLine();

            User* me = network.getUser(auth.getCurrentUser());
            if (!me) { cout << "Current user not found\n"; continue; }

            me->unblockUser(target);
            cout << "Unblocked\n";
        }

        else if (cmd == "search") {
            string key;
            cin >> key;
            eatLine();

            auto results = network.searchUser(key);
            if (results.empty()) cout << "No users\n";
            else for (const auto& r : results) cout << r << "\n";
        }

        else if (cmd == "save") {
            eatLine();
            FileManager::save(&network);
            cout << "Saved\n";
        }

        else if (cmd == "exit") {
            eatLine();
            FileManager::save(&network);
            break;
        }

        else {
            eatLine();
            cout << "Unknown command (type help)\n";
        }
    }

    return 0;
}
