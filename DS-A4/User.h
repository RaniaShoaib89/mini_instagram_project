#include <string>
#include <ctime>
#include "Queue.h"
#include "Stack.h"
#include "Message.h"

#pragma once
#define USER_H


using namespace std;



class User
{
private:

	bool isPublic;
	string username;
	string password;
	long lastLogin;
	string city;
	Queue<Message> inbox; 
	Stack<Message> sentMessages;

public:
	User(string u, string p, string city, bool isPublic);
	string getUserName() const;
	string getPassword() const;
	string getCity() const;

	void setUsername(string x);
	void setPassword(string x);

	User(const User& other);
	User& operator=(const User& other);
	bool operator==(const User& other);

	bool is_Public();

	void sendMessage(User& receiver, const string& content);
	void receiveMessage(const Message& msg);
	void viewInbox();
	void viewSentMessages();

};

