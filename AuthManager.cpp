#include "AuthManager.h"
using namespace std;

AuthManager::AuthManager() : network(nullptr) {}

AuthManager::AuthManager(Network* network) : network(network) {}

bool AuthManager::registerUser(const string& username, const string& password) {
    if (!network) return false;
    return network->addUser(username, password);
}

bool AuthManager::login(const string& username, const string& password) {
    if (!network) return false;
    if (!network->checkPassword(username, password)) return false;
    currentUser = username;
    return true;
}

void AuthManager::logout() {
    currentUser = "";
}

bool AuthManager::isLoggedIn() const {
    return !currentUser.empty();
}

string AuthManager::getCurrentUser() const {
    return currentUser;
}
