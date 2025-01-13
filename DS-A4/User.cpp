#include "User.h"
#include "Graph.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <string>
using namespace std;


User::User(string u, string p, string city = "", bool isPublic = true)
{
	this->username = u;
	this->password = p;
	this->city = city;
	this->lastLogin = time(0);
	this->isPublic = isPublic;
}

string User::getUserName() const { return username; }
void User::setUsername(string x) { username = x; };
string User::getPassword() const { return password; }
void User::setPassword(string x) { password = x; };
string User::getCity() const {return city; }

bool User::is_Public()
{
	return isPublic;
}

User::User(const User& other) 
{
	username = other.username;
	password = other.password;
	city = other.city;
	isPublic = this->isPublic;
	inbox = other.inbox;
	sentMessages = other.sentMessages;
}

User& User::operator=(const User& other) 
{
	if (this != &other) {
		username = other.username;
		password = other.password;
		city = other.city;
		isPublic = this->isPublic;
		inbox = other.inbox;
		sentMessages = other.sentMessages;
	}
	return *this;
}

bool User::operator==(const User& other)
{
	return (password == other.password && username == other.username && isPublic == other.isPublic);
}

void User::sendMessage(User& receiver, const string& content)
{
	Message msg(username, receiver.getUserName(), content);
	receiver.receiveMessage(msg);  // Receiver gets the message
	sentMessages.push(msg);  // The message is added to sent messages
}


void User::receiveMessage(const Message& msg)
{
	inbox.push(msg);  // Received messages go into the inbox
}


void User::viewInbox()
{
	cout << "Inbox for " << username << ":\n";
	while (!inbox.empty())
	{
		Message msg = inbox.Front();
		msg.displayMessage();
		inbox.pop();
	}
}


void User::viewSentMessages()
{
	cout << "Sent Messages from " << username << ":\n";
	while (!sentMessages.empty())
	{
		Message msg = sentMessages.top();
		msg.displayMessage();
		sentMessages.pop();
	}
}