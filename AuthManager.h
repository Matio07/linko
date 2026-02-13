#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include "Network.h"

class AuthManager {
private:
    Network* network;
    std::string currentUser;

public:
    AuthManager();
    AuthManager(Network* network);

    bool registerUser(const std::string& username, const std::string& password);
    bool login(const std::string& username, const std::string& password);
    void logout();

    bool isLoggedIn() const;
    std::string getCurrentUser() const;
};

#endif
