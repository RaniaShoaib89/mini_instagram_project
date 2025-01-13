#include "User.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip> 
#include <string>
#include "ListNode.h"

#pragma once
#define POST_H

using namespace std;

class Post {
private:
   
    string postContent;
    time_t timestamp;
    ListNode<User*>* likedby;
    User* user;
    int likes;
   

public:
  
    Post(string content = "", User* user = nullptr)
        : postContent(content), user(user), likedby(nullptr) , likes(0){
        timestamp = time(nullptr);

    }

    

    void likePost(User* user) {
        if (!user) return;

        if (!likedby) {
            likedby = new ListNode<User*>(user);
            likes++;
            cout << user->getUserName() << " liked the post." << endl;
            return;
        }

        ListNode<User*>* temp = likedby;
        while (temp) {
            if (temp->data == user) {
                cout << user->getUserName() << " has already liked this post." << endl;
                return;
            }
            if (!temp->next) break;
            temp = temp->next;
        }

        temp->next = new ListNode<User*>(user);
        likes++;
        cout << user->getUserName() << " liked the post." << endl;
    }

    void unlikePost(User* user) {
        if (!user || !likedby) return;

        ListNode<User*>* temp = likedby;

        if (temp->data == user) {
            likedby = temp->next;
            cout << user->getUserName() << " unliked the post." << endl;
            likes--;
            delete temp;
            return;
        }

        while (temp->next) {
            if (temp->next->data == user) {
                ListNode<User*>* delnode = temp->next;
                temp->next = delnode->next;
                cout << user->getUserName() << " unliked the post." << endl;
                delete delnode;
                likes--;
                return;
            }
            temp = temp->next;
        }

        cout << user->getUserName() << " has not liked this post." << endl;
    }

    void displayPost() {
        cout << "Post by " << user->getUserName() << ": " << postContent << endl;

        std::tm timeInfo;
        localtime_s(&timeInfo, &timestamp);

        std::ostringstream timeStream;
        timeStream << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

        cout << "Posted at: " << timeStream.str() << endl;
        cout << "Likes: " << likes << " ";
        cout << "Liked by: ";
        if (!likedby) {
            cout << "No likes yet." << endl;
            return;
        }

        ListNode<User*>* temp = likedby;
        while (temp) {
            cout << temp->data->getUserName() << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    Post(const Post& other)
        : postContent(other.postContent), user(other.user), likes(other.likes), timestamp(other.timestamp), likedby(nullptr) {

        
        if (other.likedby != nullptr) {
            ListNode<User*>* temp = other.likedby;
            likedby = new ListNode<User*>(temp->data); 
            ListNode<User*>* current = likedby;
            temp = temp->next;

         
            while (temp != nullptr) {
                current->next = new ListNode<User*>(temp->data); 
                current = current->next;
                temp = temp->next;
            }
        }
    }
    bool operator==(const Post& other)
    {
        return (user == other.user && postContent == other.postContent && timestamp == other.timestamp);
    }
    
    Post& operator=(const Post& other) {
        if (this == &other) return *this;  

      
        ListNode<User*>* temp;
        while (likedby) {
            temp = likedby;
            likedby = likedby->next;
            delete temp;
        }

        
        postContent = other.postContent;
        user = other.user;
        likes = other.likes;
        timestamp = other.timestamp;
        likedby = nullptr;  

       
        if (other.likedby != nullptr) {
            ListNode<User*>* temp = other.likedby;
            likedby = new ListNode<User*>(temp->data); 
            ListNode<User*>* current = likedby;
            temp = temp->next;

            while (temp != nullptr) {
                current->next = new ListNode<User*>(temp->data); 
                current = current->next;
                temp = temp->next;
            }
        }

        return *this;  
    }

    ~Post() {
        ListNode<User*>* temp;
        while (likedby) {
            temp = likedby;
            likedby = likedby->next;
            delete temp;
        }
    }

  
};
