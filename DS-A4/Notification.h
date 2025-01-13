#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip> 


#pragma once
#define NOTIFICATION_H

using namespace std;
class Notification
{
private:
	string content;
	time_t timestamp;
    


public:

	Notification(string content = "")
	{
		this->content = content;
		timestamp = time(nullptr);
	}

    void displayNotification() {
      cout<< content << endl;

        std::tm timeInfo;
        localtime_s(&timeInfo, &timestamp);

        std::ostringstream timeStream;
        timeStream << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

        cout <<" "<<timeStream.str() << endl;
     
  
      
    }
    Notification& operator=(const Notification& other) {
        if (this == &other) return *this;


      


        content = other.content;   
        timestamp = other.timestamp;
 
           

        return *this;
    }

};

