#include "Graph.h"

GraphNode::GraphNode(User* user) 
    : user(user), next(nullptr), followers(nullptr), following(nullptr), followerCount(0), followingCount(0), postCount(0) {}

string GraphNode::getUsername() const 
{
    return user->getUserName();
}

void GraphNode::printFollowers() const
{
    cout << "Total followers: " << followerCount << endl;
    cout << "Followers of " << getUsername() << ": ";
    if (!followers) {
        cout << "None" << endl;
        return;
    }
    GraphNode* temp = followers;
    while (temp) {
        cout << temp->getUsername() << " ";
        temp = temp->next;
    }
    cout << endl;
}

void GraphNode::printFollowing() const 
{
    cout << "Total following: " << followingCount << endl;
    cout << getUsername() << "'s Followings: ";
    if (!following) {
        cout << "None" << endl;
        return;
    }
    GraphNode* temp = following;
    while (temp) {
        cout << temp->getUsername() << " ";
        temp = temp->next;
    }
    cout << endl;
}

void GraphNode::printPendingRequests() {
    cout << "Pending follow requests for " << getUsername() << ": ";
    pendingRequests.display();
}


void GraphNode::createPost(const string& content) {
    Post newPost(content, user);
    posts.push(newPost);
    cout << user->getUserName() << " created a new post: " << content << endl;
    postCount++;
}

void GraphNode::viewPosts() {
    if (posts.empty()) {
        cout << user->getUserName() << " has no posts." << endl;
        return;
    }
    cout << "Total posts by " << user->getUserName() << ": " << postCount << endl;
    cout << "Posts by " << user->getUserName() << ":" << endl;
    Stack<Post> tempStack = posts;
    while (!tempStack.empty()) {

        tempStack.top().displayPost();
        tempStack.pop();
    }
}

//????????????????????????????????????????????????????????????????//

void Graph::search()
{
    users.displayInOrder();
}

void Graph::sendMessage(const string& senderUsername, const string& receiverUsername, const string& content)
{
    if (!userDatabase.find(senderUsername) || !userDatabase.find(receiverUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    if (isBlocked(senderUsername, receiverUsername))
    {
        cout << "Can not send message ";
        cout << senderUsername << " has blocked " << receiverUsername << endl;
        return;
    }

    if (isBlocked(receiverUsername, senderUsername))
    {
        cout << "Can not send message";
        cout << receiverUsername << " has blocked " << senderUsername << endl;
        return;
    }

    GraphNode* senderNode = userDatabase.get(senderUsername);
    GraphNode* receiverNode = userDatabase.get(receiverUsername);

    if (receiverNode->user->is_Public())
    {
        cout << "User has a Public account ";
    }

    Notification note(senderUsername + " sent you a message!");
    receiverNode->notifications.push(note);
    Message m1(senderUsername, receiverUsername, content);
    senderNode->outbox.push(m1);
    receiverNode->inbox.push(m1);

    //receiverNode->pendingRequests.push(senderUsername);
}

 // Display all messages in inbox for a user
void Graph::viewInbox(const string& username)
{
    GraphNode* usernode = userDatabase.get(username);
    if (!userDatabase.find(username)) {
        cout << "user do not exist!" << endl;
        return;
    }
    Stack<Message> tempStack = usernode->inbox;

    while (!tempStack.empty())
    {
        tempStack.top().displayMessage();
        tempStack.pop();

    }
}

// Display all sent messages for a user
void Graph::viewSentMessages(const string& username)
{

    GraphNode* usernode = userDatabase.get(username);
    if (!userDatabase.find(username)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }
    Stack<Message> tempStack = usernode->outbox;
    if (!tempStack.empty())
    {
        tempStack.top().displayMessage();
        return;
    }
    cout << "outbox is empty";


}

void Graph::addUser(const string& username, const string& password, const string& city, bool isPublic) {
    if (userDatabase.find(username)) {
        cout << "User already exists!" << endl;
        return;
    }

    User* newUser = new User(username, password, city, isPublic);
    GraphNode* newNode = new GraphNode(newUser);
    userDatabase.insert(username, newNode);
    users.insert(*newUser);
    cout << "User " << username << " added successfully!" << endl;
}


void Graph::sendFollowRequest(const string& senderUsername, const string& receiverUsername) {

    if (!userDatabase.find(senderUsername) || !userDatabase.find(receiverUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }


    if (isBlocked(senderUsername, receiverUsername))
    {
        cout << "Can not send follow request ";
        cout << senderUsername << " has blocked " << receiverUsername << endl;
        return;
    }

    if (isBlocked(receiverUsername, senderUsername))
    {
        cout << "Can not send follow request ";
        cout << receiverUsername << " has blocked " << senderUsername << endl;
        return;
    }


    GraphNode* senderNode = userDatabase.get(senderUsername);
    GraphNode* receiverNode = userDatabase.get(receiverUsername);

    if (receiverNode->user->is_Public())
    {
        cout << "User has a Public account ";
        followUser(senderUsername, receiverUsername);
        return;
    }

    Notification note(senderUsername + " sent you a friend request!");
    receiverNode->notifications.push(note);
    receiverNode->pendingRequests.push(senderUsername);
}


void Graph::acceptFollowRequest(const string& receiverUsername) {
    if (!userDatabase.find(receiverUsername)) {
        cout << "User does not exist!" << endl;
        return;
    }

    GraphNode* receiverNode = userDatabase.get(receiverUsername);

    if (receiverNode->pendingRequests.empty()) {
        cout << "No pending follow requests for " << receiverUsername << endl;
        return;
    }


    cout << "Pending follow requests for " << receiverUsername << ":" << endl;
    Queue<string> tempQueue = receiverNode->pendingRequests;
    vector<string> pendingList;

    int index = 1;
    while (!tempQueue.empty()) {
        string senderUsername = tempQueue.Front();
        pendingList.push_back(senderUsername);
        cout << index++ << ". " << senderUsername << endl;
        tempQueue.pop();
    }


    cout << "Enter the number of the request you want to accept (or 0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "No follow request accepted." << endl;
        return;
    }

    if (choice < 1 || choice > pendingList.size()) {
        cout << "Invalid choice!" << endl;
        return;
    }


    string senderUsername = pendingList[choice - 1];
    Queue<string> newQueue;


    while (!receiverNode->pendingRequests.empty()) {
        if (receiverNode->pendingRequests.Front() != senderUsername) {
            newQueue.push(receiverNode->pendingRequests.Front());
        }
        receiverNode->pendingRequests.pop();
    }

    receiverNode->pendingRequests = newQueue;


    followUser(senderUsername, receiverUsername);
    cout << "Accepted follow request from " << senderUsername << endl;
}

void Graph::followUp(const string& followerUsername, const string& followingUsername)
{
    if (!userDatabase.find(followerUsername) || !userDatabase.find(followingUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }
    GraphNode* follwowernode = userDatabase.get(followerUsername);
    GraphNode* follwowingnode = userDatabase.get(followingUsername);

    if (follwowingnode->user->is_Public() == true)
    {
        followUser(followerUsername, followingUsername);

    }
    else
    {
        cout << "user account is private. Try sending follow request";

    }

}


void Graph::declineFollowRequest(const string& receiverUsername) {
    if (!userDatabase.find(receiverUsername)) {
        cout << "User does not exist!" << endl;
        return;
    }

    GraphNode* receiverNode = userDatabase.get(receiverUsername);

    if (receiverNode->pendingRequests.empty()) {
        cout << "No pending follow requests for " << receiverUsername << endl;
        return;
    }


    cout << "Pending follow requests for " << receiverUsername << ":" << endl;
    Queue<string> tempQueue = receiverNode->pendingRequests;
    vector<string> pendingList;
    int index = 1;

    while (!tempQueue.empty()) {
        string senderUsername = tempQueue.Front();
        pendingList.push_back(senderUsername);
        cout << index++ << ". " << senderUsername << endl;
        tempQueue.pop();
    }


    cout << "Enter the number of the request to decline (or 0 to cancel): ";
    int choice;
    cin >> choice;

    if (choice == 0) {
        cout << "No request declined." << endl;
        return;
    }

    if (choice < 1 || choice > pendingList.size()) {
        cout << "Invalid choice!" << endl;
        return;
    }

    string senderUsername = pendingList[choice - 1];


    Queue<string> newQueue;
    bool found = false;
    while (!receiverNode->pendingRequests.empty()) {
        string pendingSender = receiverNode->pendingRequests.Front();
        receiverNode->pendingRequests.pop();

        if (pendingSender == senderUsername) {
            found = true;
        }
        else {
            newQueue.push(pendingSender);
        }
    }
    receiverNode->pendingRequests = newQueue;

    if (found) {
        cout << "Declined follow request from " << senderUsername << "." << endl;
    }
    else {
        cout << "No request from " << senderUsername << " found." << endl;
    }
}

void Graph::managePendingRequests(const string& receiverUsername) {

    if (!userDatabase.find(receiverUsername)) {
        cout << "User does not exist!" << endl;
        return;
    }

    GraphNode* receiverNode = userDatabase.get(receiverUsername);


    if (receiverNode->pendingRequests.empty()) {
        cout << "No pending follow requests for " << receiverUsername << "." << endl;
        return;
    }


    cout << "Pending follow requests for " << receiverUsername << ":" << endl;
    showPendingRequests(receiverUsername);

    vector<string> pendingList;


    Queue<string> tempQueue = receiverNode->pendingRequests;
    while (!tempQueue.empty()) {
        pendingList.push_back(tempQueue.Front());
        tempQueue.pop();
    }

    while (true) {
        cout << "\nEnter the number of the request to manage (or 0 to exit): ";
        int choice;
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting pending requests management." << endl;
            break;
        }

        if (choice < 1 || choice > pendingList.size()) {
            cout << "Invalid choice!" << endl;
            continue;
        }

        string senderUsername = pendingList[choice - 1];


        cout << "\nWhat would you like to do with the request from " << senderUsername << "?" << endl;
        cout << "1. Accept\n2. Decline\n3. Leave it\nEnter your choice: ";
        int action;
        cin >> action;

        if (action == 1) {

            Queue<string> newQueue;
            while (!receiverNode->pendingRequests.empty()) {
                if (receiverNode->pendingRequests.Front() != senderUsername) {
                    newQueue.push(receiverNode->pendingRequests.Front());
                }
                receiverNode->pendingRequests.pop();
            }
            receiverNode->pendingRequests = newQueue;

            Notification note(receiverUsername + " has accepted your follow request");
            GraphNode* senderNode = userDatabase.get(senderUsername);
            senderNode->notifications.push(note);
            followUser(senderUsername, receiverUsername);
            pendingList.erase(pendingList.begin() + (choice - 1));
        }
        else if (action == 2) {

            Queue<string> newQueue;
            while (!receiverNode->pendingRequests.empty()) {
                string pendingSender = receiverNode->pendingRequests.Front();
                receiverNode->pendingRequests.pop();

                if (pendingSender != senderUsername) {
                    newQueue.push(pendingSender);
                }
            }
            receiverNode->pendingRequests = newQueue;
            pendingList.erase(pendingList.begin() + (choice - 1));
        }

        else {
            break;
        }

        if (!pendingList.empty()) {
            cout << "\nUpdated pending follow requests for " << receiverUsername << ":" << endl;
            for (int i = 0; i < pendingList.size(); i++) {
                cout << i + 1 << ". " << pendingList[i] << endl;
            }
        }
        else {
            cout << "\nNo more pending requests for " << receiverUsername << "." << endl;
            break;
        }
    }
}


void Graph::followUser(const string& followerUsername, const string& followingUsername) {

    GraphNode* followerNode = userDatabase.get(followerUsername);
    GraphNode* followingNode = userDatabase.get(followingUsername);

    if (!followerNode || !followingNode) {
        cout << "Error: One or both users do not exist." << endl;
        return;
    }

    if (followerUsername == followingUsername) {
        cout << "Error: A user cannot follow themselves." << endl;
        return;
    }

    if (isBlocked(followingUsername, followerUsername))
    {
        cout << followingUsername << " has blocked " << followerUsername << endl;
        return;
    }

    if (isBlocked(followerUsername, followingUsername))
    {
        cout << followerUsername << " has blocked " << followingUsername << endl;
        return;
    }

    GraphNode* currentFollowing = followerNode->following;
    while (currentFollowing) {
        if (currentFollowing == followingNode) {
            cout << followerUsername << " is already following " << followingUsername << endl;
            return;
        }
        currentFollowing = currentFollowing->next;
    }


    GraphNode* tempFollowing = followerNode->following;
    followerNode->following = followingNode;
    followingNode->next = tempFollowing;
    followerNode->followingCount++;


    GraphNode* tempFollower = followingNode->followers;
    followingNode->followers = followerNode;
    followerNode->next = tempFollower;
    followingNode->followerCount++;


    Notification note(followerUsername + " has followed you");
    followingNode->notifications.push(note);

    cout << followerUsername << " is now following " << followingUsername << endl;
}

void Graph::unfollowUser(const string& followerUsername, const string& followingUsername) {

    GraphNode* followerNode = userDatabase.get(followerUsername);
    GraphNode* followingNode = userDatabase.get(followingUsername);

    if (!followerNode || !followingNode) {
        cout << "Error: One or both users do not exist." << endl;
        return;
    }

    if (followerUsername == followingUsername) {
        cout << "Error: A user cannot unfollow themselves." << endl;
        return;
    }


    GraphNode* prevFollowing = nullptr;
    GraphNode* currentFollowing = followerNode->following;

    while (currentFollowing) {
        if (currentFollowing == followingNode) {

            if (prevFollowing) {
                prevFollowing->next = currentFollowing->next;
            }
            else {
                followerNode->following = currentFollowing->next;
            }
            followerNode->followingCount--;
            currentFollowing->next = nullptr;
            break;
        }
        prevFollowing = currentFollowing;
        currentFollowing = currentFollowing->next;
    }


    GraphNode* prevFollower = nullptr;
    GraphNode* currentFollower = followingNode->followers;

    while (currentFollower) {
        if (currentFollower == followerNode) {

            if (prevFollower) {
                prevFollower->next = currentFollower->next;
            }
            else {
                followingNode->followers = currentFollower->next;
            }
            followingNode->followerCount--;
            currentFollower->next = nullptr;
            break;
        }
        prevFollower = currentFollower;
        currentFollower = currentFollower->next;
    }

}

void Graph::showPendingRequests(const string& username) {
    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    userDatabase.get(username)->printPendingRequests();
}

void Graph::showFollowers(const string& username) {
    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    userDatabase.get(username)->printFollowers();
}


void Graph::showFollowing(const string& username) {
    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    userDatabase.get(username)->printFollowing();
}

bool Graph::login(const string& username, const string& password) {

    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return false;
    }


    GraphNode* userNode = userDatabase.get(username);


    if (userNode->user->getPassword() == password) {
        cout << "Login successful! Welcome, " << username << "." << endl;
        return true;
    }
    else {
        cout << "Invalid password. Please try again." << endl;
        return false;
    }
}

void Graph::createPost(const string& username, const string& content) {
    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    userDatabase.get(username)->createPost(content);
    Post newPost(content, userDatabase.get(username)->user);
    GraphNode* tempFollower = userDatabase.get(username)->followers;
    while (tempFollower != nullptr) {
        tempFollower->newsFeed.push(newPost);
        tempFollower = tempFollower->next;
    }
}


void Graph::viewPosts(const string& username) {

    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    cout << username << " posts: " << endl;
    userDatabase.get(username)->viewPosts();
}

void Graph::unlikeRecentPost(const string& likerUsername, const string& likeeUsername) {

    if (!userDatabase.find(likerUsername) || !userDatabase.find(likeeUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    GraphNode* likerNode = userDatabase.get(likerUsername);
    GraphNode* likeeNode = userDatabase.get(likeeUsername);

    bool followsLikee = false;
    GraphNode* tempFollowing = likerNode->following;
    while (tempFollowing) {
        if (tempFollowing->user->getUserName() == likeeUsername) {
            followsLikee = true;
            break;
        }
        tempFollowing = tempFollowing->next;
    }

    if (!followsLikee) {
        cout << likerUsername << " must follow " << likeeUsername << " to like their posts." << endl;
        return;
    }


    if (likeeNode->posts.empty()) {
        cout << likeeUsername << " has no posts to like." << endl;
        return;
    }

    Post postTounLike = likeeNode->posts.top();
    postTounLike.unlikePost(likerNode->user);

    likeeNode->posts.pop();
    likeeNode->posts.push(postTounLike);



    cout << likerUsername << " unliked a post by " << likeeUsername << "." << endl;
}

void Graph::likeRecentPost(const string& likerUsername, const string& likeeUsername) {
    if (!userDatabase.find(likerUsername) || !userDatabase.find(likeeUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    GraphNode* likerNode = userDatabase.get(likerUsername);
    GraphNode* likeeNode = userDatabase.get(likeeUsername);

    bool followsLikee = false;
    GraphNode* tempFollowing = likerNode->following;
    while (tempFollowing) {
        if (tempFollowing->user->getUserName() == likeeUsername) {
            followsLikee = true;
            break;
        }
        tempFollowing = tempFollowing->next;
    }

    if (!followsLikee) {
        cout << likerUsername << " must follow " << likeeUsername << " to like their posts." << endl;
        return;
    }

    if (likeeNode->posts.empty()) {
        cout << likeeUsername << " has no posts to like." << endl;
        return;
    }


    Post postToLike = likeeNode->posts.top();
    postToLike.likePost(likerNode->user);

    likeeNode->posts.pop();
    likeeNode->posts.push(postToLike);

    cout << likerUsername << " liked a post by " << likeeUsername << "." << endl;
}


void Graph::VisitProfile(const string& visiterUsername, const string& visitingUsername) {
    if (!userDatabase.find(visitingUsername) || !userDatabase.find(visiterUsername)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    if (visitingUsername == visiterUsername)
    {
        return;
    }
    
    GraphNode* visiterNode = userDatabase.get(visiterUsername);
    GraphNode* visitingNode = userDatabase.get(visitingUsername);


    bool followsVisiting = false;
    GraphNode* tempFollowing = visiterNode->following;
    while (tempFollowing) {
        if (tempFollowing->user->getUserName() == visitingUsername) {
            followsVisiting = true;
            break;
        }
        tempFollowing = tempFollowing->next;
    }

    if (!followsVisiting) {
        cout << visiterUsername << " must follow " << visitingUsername << " to visit their profile." << endl;
        return;
    }

    if (visitingNode->posts.empty()) {
        cout << visitingUsername << " has not posted." << endl;
        return;
    }

    Stack<Post> tempStack;
    while (!visitingNode->posts.empty()) {
        tempStack.push(visitingNode->posts.top());
        visitingNode->posts.pop();
    }


    cout << visitingUsername << "'s Profile: " << endl;
    cout << "Click 'L' to like a post, 'U' to unlike post or press Enter to skip." << endl;

    char ch;
    while (!tempStack.empty()) {

        Post currentPost = tempStack.top();
        currentPost.displayPost();


        cin >> ch;
        if (ch == 'L' || ch == 'l') {
            currentPost.likePost(visiterNode->user);
        }
        if (ch == 'U' || ch == 'u') {
            currentPost.unlikePost(visiterNode->user);
        }



        visitingNode->posts.push(currentPost);
        tempStack.pop();
    }

    while (!visitingNode->posts.empty()) {
        tempStack.push(visitingNode->posts.top());
        visitingNode->posts.pop();
    }
    while (!tempStack.empty()) {
        visitingNode->posts.push(tempStack.top());
        tempStack.pop();
    }

    cout << "Profile visit ended." << endl;
}


void Graph::viewNewsFeed(string userName)
{
    if (!userDatabase.find(userName))
    {
        cout << "Username not found! ";
        return;
    }
    GraphNode* user = userDatabase.get(userName);
    Stack<Post> tempStack = user->newsFeed;

    cout << userName << " newsfeed" << endl;
    while (!tempStack.empty())
    {
        tempStack.top().displayPost();
        tempStack.pop();


    }
}


void Graph::deleteRecentPost(string username)
{

    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }


    GraphNode* delpostUser = userDatabase.get(username);


    if (delpostUser->posts.empty()) {
        cout << "No posts to delete for this user!" << endl;
        return;
    }


    Post recentPost = delpostUser->posts.top();
    delpostUser->posts.pop();
    delpostUser->postCount--;


    cout << "Recent post deleted from user: " << username << endl;


    GraphNode* temp = delpostUser->followers;
    while (temp != nullptr)
    {
        Stack<Post>& followerNewsfeed = temp->newsFeed;


        Stack<Post> tempStack;


        bool postRemoved = false;


        while (!followerNewsfeed.empty()) {
            Post post = followerNewsfeed.top();
            followerNewsfeed.pop();

            if (post == recentPost && !postRemoved) {
                postRemoved = true;
                cout << "Post removed from follower's newsfeed." << endl;
                continue;
            }

            tempStack.push(post);
        }


        while (!tempStack.empty()) {
            Post post = tempStack.top();
            tempStack.pop();
            followerNewsfeed.push(post);
        }

        temp = temp->next;
    }
}


void Graph::viewNotifications(string userName)
{
    if (!userDatabase.find(userName))
    {
        cout << "Username not found! ";
        return;
    }
    GraphNode* userNode = userDatabase.get(userName);

    while (!userNode->notifications.empty())
    {
        userNode->notifications.Front().displayNotification();
        userNode->notifications.pop();

    }

    cout << endl;

}


void Graph::forgetPassword(string userName, string newPassword)
{
    if (!userDatabase.find(userName))
    {
        cout << "Username not found! ";
        return;
    }

    GraphNode* userNode = userDatabase.get(userName);

    userNode->user->setPassword(newPassword);
    cout << "New password set" << endl;

}

void Graph::blockUser(const string& blocker, const string& blockee) {
    if (!userDatabase.find(blockee) || !userDatabase.find(blocker)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    GraphNode* blockerNode = userDatabase.get(blocker);
    GraphNode* blockeeNode = userDatabase.get(blockee);


    unfollowUser(blocker, blockee);
    unfollowUser(blockee, blocker);


    blockerNode->blockedUsers.push(blockee);
    cout << blocker << " has successfully blocked " << blockee << endl;
}


void Graph::unblockUser(const string& blocker, const string& blockee) {
    if (!userDatabase.find(blockee) || !userDatabase.find(blocker)) {
        cout << "One or both users do not exist!" << endl;
        return;
    }

    GraphNode* blockerNode = userDatabase.get(blocker);


    Stack<string> tempStack;
    bool found = false;


    while (!blockerNode->blockedUsers.empty()) {
        string blocked = blockerNode->blockedUsers.top();
        blockerNode->blockedUsers.pop();

        if (blocked == blockee) {
            found = true;
            continue;
        }

        tempStack.push(blocked);
    }


    while (!tempStack.empty()) {
        blockerNode->blockedUsers.push(tempStack.top());
        tempStack.pop();
    }

    if (found) {
        cout << blocker << " has successfully unblocked " << blockee << endl;
    }
    else {
        cout << blockee << " is not in " << blocker << "'s blocked list." << endl;
    }
}


bool Graph::isBlocked(const string& blocker, const string& blockee) {
    if (!userDatabase.find(blockee) || !userDatabase.find(blocker)) {
        cout << "One or both users do not exist!" << endl;
        return false;
    }

    GraphNode* blockerNode = userDatabase.get(blocker);


    Stack<string> tempStack = blockerNode->blockedUsers;
    while (!tempStack.empty()) {
        if (tempStack.top() == blockee) {
            return true;
        }
        tempStack.pop();
    }

    return false;
}

void Graph::viewBlockedUsers(const string& username) {
    if (!userDatabase.find(username)) {
        cout << "User does not exist!" << endl;
        return;
    }

    GraphNode* user = userDatabase.get(username);

    if (user->blockedUsers.empty()) {
        cout << "User has no blocked users" << endl;
    }
    else {
        cout << "Block List of " << username << endl;
        Stack<string> tempStack = user->blockedUsers;
        while (!tempStack.empty()) {
            cout << tempStack.top() << " ";
            tempStack.pop();
        }
        cout << endl;
    }
}