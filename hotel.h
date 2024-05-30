#ifndef PROJECTQT_HOTEL_H
//#define PROJECTQT_HOTEL_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>

struct Room {
public:
    int roomID;
    std::string type;
    int guestsNumber;
    bool safe;
    bool miniBar;
    bool isMerged;
    bool isFree;
    float square;
    int priceNight;
};

std::ostream& operator<<(std::ostream& os, const Room& room);

struct Booking {
public:
    int bookingID;
    int roomID;
    std::string guestFirstName;
    std::string guestSecondName;
    std::string guestPhone;
    std::string checkInDate;
    std::string checkOutDate;
};

std::ostream& operator<<(std::ostream& os, const Booking& booking);

class BookingSystem {
private:
    std::vector<Room> rooms;
    std::vector<Booking> bookings;
public:
    std::string booking_path = "/Users/andreybobua/CLionProjects/ProjectQT/bookings_set.csv";
    std::string room_path = "/Users/andreybobua/CLionProjects/ProjectQT/rooms_set.csv";

    static bool stb(std::string& value);

    static std::vector<std::string> splitter(const std::string &s);

    static std::vector<Room> readRoom_csv(const std::string& path);

    static std::vector<Booking> readBooking_csv(const std::string& path);

    static void appendBookingToCSV(const std::string& filePath, const Booking& booking);

//    static void updateFile(const std::string& path, const std::string& operation, Booking& booking) {
//
//        if (operation == "add") {
//            appendBookingToCSV("/Users/andreybobua/CLionProjects/ProjectQT/bookings_set.csv", booking);
//            std::cout << "Booking added successfully!\n";
//        }
//        else if (operation == "del") {
//
//        }
//    }

    bool checkBooking(const int& bookingID);

    bool checkRoom(const int& roomID);

    void createBooking(const Room& room, const std::string& guestFirstName, const std::string& guestSecondName, const std::string& guestPhone, const std::string& checkInDate, const std::string& checkOutDate);

    void adjustBooking(Booking booking, const int& bookingID, const std::string& newCheckInDate, const std::string& newCheckOutDate);

    void cancelBooking(int bookingID);
};

#endif //PROJECTQT_HOTEL_H
