#include <iostream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#include "MaxHeap.h"
#include "User.h"
#include "Hashmap.h"
#include "Post.h"
#include "Graph.h"
using namespace std;

// Password strength function
int passwordStrength(string str) 
{
    if (str.length() < 8) 
    {
        return 0;
    }
    int score = 0;
    int numOfAlphabets = 0;
    int numOfNumbers = 0;
    int numOdSpeciaCharacters = 0;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 65 && str[i] <= 90) {
            numOfAlphabets++;
        }
        if (isdigit(str[i])) {
            numOfNumbers++;
        }
        if ((str[i] >= 58 && str[i] <= 64) || (str[i] >= 33 && str[i] <= 47)) {
            numOdSpeciaCharacters++;
        }
    }

    if (numOdSpeciaCharacters >= 1) {
        score++;
    }
    if (numOfNumbers >= 1) {
        score++;
    }
    if (numOfAlphabets >= 1) {
        score++;
    }

    return score;
}

// Function to rate password strength
string rateStrength(int score) {
    switch (score) {
    case 0: return "invalid";
    case 1: return "weak";
    case 2: return "moderate";
    case 3: return "strong";
    default: return "";
    }
}

int main() {
    Graph instagram;  // Assumes a Graph object is used to manage user accounts
    string username, password, username2, city, postContent;
    string receiver, messageContent;
    bool ispublic;
    int choice;

    instagram.addUser("maham", "1Maham.noor", "FSD", 1);
    instagram.addUser("rania", "1Maham.noor", "FSD", 0);
    instagram.addUser("mobeen", "1Maham.noor", "LHR", 0);
    instagram.addUser("ahmed", "1Maham.noor", "ISL", 0);
    instagram.addUser("ayesha", "1Maham.noor", "LHR", 1);
    instagram.addUser("noor", "1Maham.noor", "ISL", 1);



    while (1) {
        cout << "----------------------------------------------------------------\n";
        cout << "\nEnter from the following choices: " << endl;
        cout << "1. Login\n";
        cout << "2. Create Account\n";
        cout << "3. Forgot Password\n";
        cout << "----------------------------------------------------------------\n";

        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;

            if (instagram.login(username, password)) {
                while (choice != 25) {
                    cout << "\nEnter from the following: " << endl;
                    cout << "------------------------------------------\n";
                    cout << "1. Search users\n2. Follow user\n3. Send Follow request\n4. View pending requests\n5. Create post\n6. Delete recent post\n";
                    cout << "7. View posts\n8. Visit user profile\n9. View notifications\n10. Manage pending requests\n11. Unfollow user\n";
                    cout << "12. Block user\n13. Unblock user\n14. View block list\n15. View newsfeed\n16. Like post\n17. Unlike post\n18. See following\n";
                    cout << "19. See followers\n20. Send Message\n21. View Inbox\n22. View Sent Message\n23. Logout\n";
                    cout << "------------------------------------------\n";

                    cin >> choice;
                    cout << endl;

                    switch (choice) {
                    case 1:  // Search users
                          instagram.search();
                        break;
                    case 2:  // Follow user
                        cout << "Enter user you want to follow: ";
                        cin >> username2;
                        instagram.followUp(username, username2);
                        break;
                    case 3:  // Send follow request
                        cout << "Enter user to send follow request: ";
                        cin >> username2;
                        instagram.sendFollowRequest(username, username2);
                        break;
                    case 4:  // View pending requests
                        instagram.showPendingRequests(username);
                        break;
                    case 5:  // Create post
                        cout << "Enter post content: ";
                        cin.ignore();
                        getline(cin, postContent);
                        instagram.createPost(username, postContent);
                        break;
                    case 6:  // Delete recent post
                        instagram.deleteRecentPost(username);
                        break;
                    case 7:  // View posts
                        instagram.viewPosts(username);
                        break;
                    case 8:  // Visit user profile
                        cout << "Enter username of the profile to visit: ";
                        cin >> username2;
                        instagram.VisitProfile(username, username2);
                        break;
                    case 9:  // View notifications
                        instagram.viewNotifications(username);
                        break;
                    case 10:  // Manage pending requests
                        instagram.managePendingRequests(username);
                        break;
                    case 11:  // Unfollow user
                        cout << "Enter username to unfollow: ";
                        cin >> username2;
                        instagram.unfollowUser(username, username2);
                        break;
                    case 12:  // Block user
                        cout << "Enter username to block: ";
                        cin >> username2;
                        instagram.blockUser(username, username2);
                        break;
                    case 13:  // Unblock user
                        cout << "Enter username to unblock: ";
                        cin >> username2;
                        instagram.unblockUser(username, username2);
                        break;
                    case 14:  // View block list
                        instagram.viewBlockedUsers(username);
                        break;
                    case 15:  // View newsfeed
                        instagram.viewNewsFeed(username);
                        break;
                    case 16:  // Like post
                        cout << "Enter post ID to like: ";
                        cin >> postContent;
                        instagram.likeRecentPost(username, postContent);
                        break;
                    case 17:  // Unlike post
                        cout << "Enter post ID to unlike: ";
                        cin >> postContent;
                        instagram.unlikeRecentPost(username, postContent);
                        break;
                    case 18:  // See following
                        instagram.showFollowing(username);
                        break;
                    case 19:  // See followers
                        instagram.showFollowers(username);
                        break;
                    case 20:  // Send message
                        //string receiver = "", messageContent = "";
                        cout << "Enter recipient username: ";
                        cin >> receiver;
                        cout << "Enter message content: ";
                        cin.ignore();
                        getline(cin, messageContent);
                        instagram.sendMessage(username, receiver, messageContent); 
                        cout << "message sent!\n";
                        break;
                    case 21:   //View inbox
                        instagram.viewInbox(username);  
                        break;
                    case 22:  // View sent message
                        instagram.viewSentMessages(username);
                        break;
                    case 23:  // Logout
                        cout << "Logging out...\n";
                        choice = 25;  // Exit inner loop
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
            else {
                cout << "Invalid username or password. Please try again." << endl;
            }
            break;
        }
        case 2: {
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter city: ";
            cin >> city;
            cout << "Enter 1 for public account and 0 for private account: ";
            cin >> ispublic;

            int strength = passwordStrength(password);
            cout << "Password strength: " << rateStrength(strength) << endl;

            if (strength < 2) {
                cout << "Weak password! Please create a stronger password." << endl;
                break;
            }

            instagram.addUser(username, password, city, ispublic);
            cout << "Account created successfully!" << endl;
            break;
        }
        case 3: {
            cout << "Enter username to reset password: ";
            cin >> username;
            cout << "Enter new password: ";
            cin >> password;
            instagram.forgetPassword(username, password);
            cout << "Password reset successfully!" << endl;
            break;
        }
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
