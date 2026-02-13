#include "AuthManager.h"
using namespace std;

AuthManager::AuthManager(Network* n) : network(n), currentUser("") {}

bool AuthManager::registerUser(const string& username, const string& password) {
    return network->addUser(username, password);
}

bool AuthManager::login(const string& username, const string& password) {
    if (network->checkPassword(username, password)) {
        currentUser = username;
        return true;
    }
    return false;
}

void AuthManager::logout() { currentUser = ""; }

bool AuthManager::isLoggedIn() const { return currentUser != ""; }

const string& AuthManager::getCurrentUser() const { return currentUser; }
