#include "Message.h"


Message::Message() : sender(""), receiver(""), content(""), timestamp(time(0)) {}

void Message::displayMessage() const
{
    time_t timestamp = time(nullptr);
    tm timeInfo;

    // Convert time_t to local time (thread-safe)
    localtime_s(&timeInfo, &timestamp);

    // Format the time into a readable string
    std::ostringstream timeStream;
    timeStream << put_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

    cout << "From: " << sender << "\nTo: " << receiver << "\nMessage: " << content
         << "\nTime: " << timeStream.str() << endl;
}