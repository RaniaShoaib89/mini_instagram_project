#include "UserBST.h"



UserBST::~UserBST() { clear(root);}

void UserBST::insert(User& user) { root = insert(root, user); }

User* UserBST::search(const string& username) const {
    Node* result = search(root, username);
    return result ? &result->user : nullptr;
}

void UserBST::displayInOrder() const {
    if (root == nullptr) {
        cout << "The tree is empty." << endl;
    }
    else {
        inOrder(root);
    }
}