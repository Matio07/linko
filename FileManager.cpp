#include "FileManager.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

static string cleanText(string s) {
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '|' || s[i] == ',' || s[i] == '\n' || s[i] == '\r') s[i] = ' ';
    }
    return s;
}

static vector<string> splitByChar(const string& s, char delim) {
    vector<string> parts;
    string cur;
    for (char c : s) {
        if (c == delim) {
            parts.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(c);
        }
    }
    parts.push_back(cur);
    return parts;
}

void FileManager::save(Network* network) {
    filesystem::create_directories("data");

    ofstream userFile("data/users.txt");
    for (const auto& pair : network->getAllUsers()) {
        const User& user = pair.second;

        userFile << user.getUsername() << "|"
                 << user.getPassword() << "|"
                 << cleanText(user.getBio()) << "|";

        const auto& followers = user.getFollowers();
        for (size_t i = 0; i < followers.size(); i++) {
            userFile << followers[i];
            if (i + 1 < followers.size()) userFile << ",";
        }
        userFile << "|";

        const auto& following = user.getFollowing();
        for (size_t i = 0; i < following.size(); i++) {
            userFile << following[i];
            if (i + 1 < following.size()) userFile << ",";
        }
        userFile << "|";

        const auto& blocked = user.getBlocked();
        for (size_t i = 0; i < blocked.size(); i++) {
            userFile << blocked[i];
            if (i + 1 < blocked.size()) userFile << ",";
        }
        userFile << "|";

        const auto& posts = user.getPosts();
        for (size_t i = 0; i < posts.size(); i++) {
            userFile << posts[i];
            if (i + 1 < posts.size()) userFile << ",";
        }

        userFile << "\n";
    }
    userFile.close();

    ofstream postFile("data/posts.txt");
    for (const auto& pair : network->getAllPosts()) {
        const Post& post = pair.second;
        postFile << post.getId() << "|"
                 << post.getAuthor() << "|"
                 << cleanText(post.getContent()) << "|"
                 << post.getLikeCount() << "|"
                 << post.getPostTime() << "\n";
    }
    postFile.close();

    ofstream commentFile("data/comments.txt");
    for (const auto& pair : network->getAllPosts()) {
        const Post& post = pair.second;
        for (const auto& c : post.getComments()) {
            commentFile << post.getId() << "|"
                        << c.getAuthor() << "|"
                        << cleanText(c.getText()) << "\n";
        }
    }
    commentFile.close();
}

void FileManager::load(Network* network) {
    ifstream userFile("data/users.txt");
    if (userFile.is_open()) {
        string line;
        while (getline(userFile, line)) {
            if (line.empty()) continue;
            auto parts = splitByChar(line, '|');
            if (parts.size() < 7) continue;

            string username = parts[0];
            string password = parts[1];
            string bio = parts[2];

            User u(username);
            u.setPassword(password);
            u.setBio(bio);

            auto followers = splitByChar(parts[3], ',');
            if (!(followers.size() == 1 && followers[0] == "")) {
                for (const auto& f : followers) u.addFollower(f);
            }

            auto following = splitByChar(parts[4], ',');
            if (!(following.size() == 1 && following[0] == "")) {
                for (const auto& f : following) u.addFollowing(f);
            }

            auto blocked = splitByChar(parts[5], ',');
            if (!(blocked.size() == 1 && blocked[0] == "")) {
                for (const auto& b : blocked) u.blockUser(b);
            }

            auto postIds = splitByChar(parts[6], ',');
            if (!(postIds.size() == 1 && postIds[0] == "")) {
                for (const auto& pid : postIds) {
                    istringstream iss(pid);
                    int id;
                    if (iss >> id) u.addPost(id);
                }
            }

            network->addUserObject(u);
        }
        userFile.close();
    }

    ifstream postFile("data/posts.txt");
    if (postFile.is_open()) {
        string line;
        int maxId = 0;
        while (getline(postFile, line)) {
            if (line.empty()) continue;
            auto parts = splitByChar(line, '|');
            if (parts.size() < 5) continue;

            int id = 0;
            int likes = 0;
            long t = 0;

            { istringstream iss(parts[0]); iss >> id; }
            string author = parts[1];
            string content = parts[2];
            { istringstream iss(parts[3]); iss >> likes; }
            { istringstream iss(parts[4]); iss >> t; }

            Post p(id, content, author);
            p.setLikeCount(likes);
            p.setPostTime(t);

            network->addPostObject(p);
            if (id > maxId) maxId = id;
        }
        network->setNextPostId(maxId + 1);
        postFile.close();
    }

    ifstream commentFile("data/comments.txt");
    if (commentFile.is_open()) {
        string line;
        while (getline(commentFile, line)) {
            if (line.empty()) continue;
            auto parts = splitByChar(line, '|');
            if (parts.size() < 3) continue;

            int postId = 0;
            { istringstream iss(parts[0]); iss >> postId; }
            string author = parts[1];
            string text = parts[2];

            Post* p = network->getPost(postId);
            if (p) p->addComment(Comment(author, text));
        }
        commentFile.close();
    }
}
