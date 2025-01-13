#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip> 
#pragma once
#define MESSAGE_H

using namespace std;


class Message
{
public:

    string sender;
    string receiver;
    string content;
    time_t timestamp;


    Message();
    Message(const string& sender, const string& receiver, const string& content)
        : sender(sender), receiver(receiver), content(content), timestamp(0) {}

    void displayMessage() const;

    Message(const Message& other)
        : receiver(other.receiver), sender(other.sender), content(other.content), timestamp(other.timestamp) {}


};

