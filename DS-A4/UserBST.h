#pragma once



#include <iostream>
#include <string>
#include "User.h"
#define USERBST_H

using namespace std;

class UserBST {
private:
    struct Node {
        User user;
        Node* left;
        Node* right;

        Node(const User& u) : user(u), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const User& user) {
        if (node == nullptr) {
            return new Node(user);
        }

        if (user.getUserName() < node->user.getUserName()) {
            node->left = insert(node->left, user);
        }
        else if (user.getUserName() > node->user.getUserName()) {
            node->right = insert(node->right, user);
        }

        return node;
    }

    Node* search(Node* node, const string& username) const {
        if (node == nullptr || node->user.getUserName() == username) {
            return node;
        }

        if (username < node->user.getUserName()) {
            return search(node->left, username);
        }
        else {
            return search(node->right, username);
        }
    }

    void inOrder(Node* node) const {
        if (node != nullptr) {
            inOrder(node->left);
            cout << "Username: " << node->user.getUserName() << ", City: " << node->user.getCity() << endl;
            inOrder(node->right);
        }
    }

   
    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:

    UserBST() : root(nullptr) {}
    ~UserBST();
    User* search(const string& username) const;
    void insert(User& user);
    void displayInOrder() const;
};
