//
// Created by Andrew B. on 08.05.2024.
//

#include "hotel.h"
#include <iostream>
#include <string>

std::ostream& operator<<(std::ostream& os, const Room& room) {
    os << "RoomID: " << room.roomID
       << ", Type: " << room.type
       << ", Guests: " << room.guestsNumber
       << ", Safe: " << (room.safe ? "Yes" : "No")
       << ", MiniBar: " << (room.miniBar ? "Yes" : "No")
       << ", IsMerged: " << (room.isMerged ? "Yes" : "No")
       << ", IsFree: " << (room.isFree ? "Yes" : "No")
       << ", Square: " << room.square
       << ", Price/Night: " << room.priceNight;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Booking& booking) {
    os << "BookingID: " << booking.bookingID
       << ", RoomID: " << booking.roomID
       << ", guestFirstName: " << booking.guestFirstName
       << ", guestSecondName: " << booking.guestSecondName
       << ", guestPhone: " << booking.guestPhone
       << ", checkInDate: " << booking.checkInDate
       << ", checkOutDate: " << booking.checkOutDate;
    return os;
}

bool BookingSystem::stb(std::string& value) {
    if (value == "true") {
        return true;
    }
    else {
        return false;
    }
}

std::vector<std::string> BookingSystem::splitter(const std::string &s) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, ';')) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Room> BookingSystem::readRoom_csv(const std::string& path) {
    std::vector<Room> outRooms;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file" << '\n';
        return outRooms;
    }
    std::getline(file, line);
    while (std::getline(file, line)) {
        Room newRoom;
        std::vector<std::string> fields = splitter(line);
        newRoom.roomID = std::stoi(fields[0]);
        newRoom.type = fields[1];
        newRoom.guestsNumber = std::stoi(fields[2]);
        newRoom.safe = stb(fields[3]);
        newRoom.miniBar = stb(fields[4]);
        newRoom.isMerged = stb(fields[5]);
        newRoom.isFree = stb(fields[6]);
        newRoom.square = std::stoi(fields[7]);
        newRoom.priceNight = std::stoi(fields[8]);
        outRooms.push_back(newRoom);
    }
    return outRooms;
}

std::vector<Booking> BookingSystem::readBooking_csv(const std::string& path) {
    std::vector<Booking> outBookings;
    std::ifstream file(path);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Could not open the file" << '\n';
        return outBookings;
    }

    std::getline(file, line);
    while (std::getline(file, line)) {
        Booking newBooking;
        std::vector<std::string> fields = splitter(line);
        newBooking.bookingID = std::stoi(fields[0]);
        newBooking.roomID = std::stoi(fields[1]);
        newBooking.guestFirstName = fields[2];
        newBooking.guestSecondName = fields[3];
        newBooking.guestPhone = fields[4];
        newBooking.checkInDate = fields[5];
        newBooking.checkOutDate = fields[5];
        outBookings.push_back(newBooking);
    }
    return outBookings;
}

void BookingSystem::appendBookingToCSV(const std::string& filePath, const Booking& booking) {
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return;
    }

    file << booking.bookingID << ';'
         << booking.roomID << ';'
         << booking.guestFirstName << ';'
         << booking.guestSecondName << ';'
         << booking.guestPhone << ';'
         << booking.checkInDate << ';'
         << booking.checkOutDate << '\n';

    file.close();
}

bool BookingSystem::checkBooking(const int& bookingID) {
    bool searchFlagB = false; // отображает, найден ли такой номер брони
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingID == bookingID) {
            searchFlagB = true;
        }
    }
    return searchFlagB;
}

//bool BookingSystem::checkRoom(const int& roomID) {
//    bool searchFlagB = false; // отображает, найден ли такой номер брони
//    for (size_t i = 0; i < rooms.size(); i++) {
//        if (bookings[i].bookingID == roomID) {
//            searchFlagB = true;
//        }
//    }
//    return searchFlagB;
//}

void BookingSystem::createBooking(const Room& room, const std::string& guestFirstName, const std::string& guestSecondName, const std::string& guestPhone, const std::string& checkInDate, const std::string& checkOutDate) {
    bool searchFlagR = false;
    for (size_t i = 0; i < rooms.size(); i++) {
        if (rooms[i].roomID == room.roomID) {
            searchFlagR = true;
        }
    }
    if (searchFlagR) {
        if (room.isFree) {
            Booking newBooking;
            newBooking.bookingID = bookings.size() + 1;
            newBooking.roomID = room.roomID;
            newBooking.guestFirstName = guestFirstName;
            newBooking.guestSecondName = guestSecondName;
            newBooking.guestPhone = guestPhone;
            newBooking.checkInDate = checkInDate;
            newBooking.checkOutDate = checkOutDate;
            bookings.push_back(newBooking);
            for (size_t i = 0; i < rooms.size(); i++) {
                if (rooms[i].roomID == room.roomID) {
                    rooms[i].isFree = false;
                }
            }
            appendBookingToCSV(booking_path, newBooking);
            std::cout << "Booking created successfully for Room ID " << room.roomID << "!\n";
        }
        else {
            std::cout << "Room " << room.roomID << " is already booked" "!\n";
        }
    }
    else {
        throw std::runtime_error("There is no room with such number. Try another room ID.");
    }
}

void BookingSystem::adjustBooking(Booking booking) {
    bool searchFlagB = false; // отображает, найден ли такой номер брони
    for (size_t i = 0; i < bookings.size(); i++) {
        if (bookings[i].bookingID == booking.bookingID) {
            searchFlagB = true;
        }
    }
    if (searchFlagB) {

        }
        std::cout << "Booking ID " << bookingID << " adjusted successfully!\n";
    }
    else {
        std::cout << "Booking ID " << bookingID << " not found!\n";
    }
}

void BookingSystem::cancelBooking(int bookingID) {
    bool searchFlagB = checkBooking(bookingID);
    if (searchFlagB) {
        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i].bookingID == bookingID) {
                bookings.erase(bookings.begin() + bookingID - 1);
            }
        }
        std::cout << "Booking ID " << bookingID << " cancelled successfully!\n";
    }
    else {
        std::cout << "Booking ID " << bookingID << " not found!\n";
    }
}