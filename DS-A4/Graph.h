#include "Hashmap.h"
#include "User.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include "Queue.h"
#include <vector>
#include "Stack.h"
#include "Message.h"
#include "UserBST.h"

#pragma once
#define GRAPH_H

using namespace std;




#include "Hashmap.h"
#include "User.h"
#include "Queue.h"
#include "Post.h"
#include "Notification.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>
#include "Message.h"

#pragma once
#define GRAPHNODE_H

using namespace std;

class GraphNode {
public:
    User* user;
    GraphNode* next;
    GraphNode* followers;
    GraphNode* following;
    Queue<string> pendingRequests;
    Stack<Post> posts;
    Stack<Post> newsFeed;
    
    Queue <Notification> notifications;
    Stack <string> blockedUsers;
    int postCount;
    int followerCount;
    int followingCount;
    Stack<Message> outbox;
    Stack<Message> inbox;

    GraphNode(User* user);
    string getUsername() const;
    void printFollowers() const;
    void printFollowing() const;
    void printPendingRequests();
    void createPost(const string& content);
    void viewPosts(); 
    ~GraphNode() {}

};

class Graph {
private:
    Hashmap<GraphNode*, string> userDatabase;
    UserBST users;
public:

    bool login(const string& username, const string& password);
    void forgetPassword(string userName, string newPassword);

    void search();
    void addUser(const string& username, const string& password, const string& city, bool isPublic);

    void sendMessage(const string& senderUsername, const string& receiverUsername, const string& content);
    void viewInbox(const string& username);
    void viewSentMessages(const string& username);

    void sendFollowRequest(const string& senderUsername, const string& receiverUsername); 
    void acceptFollowRequest(const string& receiverUsername); 

    void followUp(const string& followerUsername, const string& followingUsername);
    void declineFollowRequest(const string& receiverUsername); 

    void managePendingRequests(const string& receiverUsername);
    void followUser(const string& followerUsername, const string& followingUsername); 
    void unfollowUser(const string& followerUsername, const string& followingUsername);
    void showPendingRequests(const string& username);

    void showFollowing(const string& username);
    void showFollowers(const string& username);

    void createPost(const string& username, const string& content); 
    void viewPosts(const string& username);
    void unlikeRecentPost(const string& likerUsername, const string& likeeUsername);
    void likeRecentPost(const string& likerUsername, const string& likeeUsername); 
    void deleteRecentPost(string username);

    void VisitProfile(const string& visiterUsername, const string& visitingUsername);
    void viewNewsFeed(string userName);
    void viewNotifications(string userName);

    void blockUser(const string& blocker, const string& blockee);
    bool isBlocked(const string& blocker, const string& blockee);
    void unblockUser(const string& blocker, const string& blockee);
    void viewBlockedUsers(const string& username);

};
