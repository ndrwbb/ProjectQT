//
// Created by Andrew B. on 08.05.2024.
//

#include "hotel.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main() {
//    std::vector<Room> rooms = BookingSystem::readRoom_csv("/Users/andreybobua/CLionProjects/ProjectQT/rooms_set.csv");
//    for (size_t i = 0; i < rooms.size(); ++i) {
//        std::cout << rooms[i] << '\n';
//    }
    std::vector<Booking> bookings = BookingSystem::readBooking_csv("/Users/andreybobua/CLionProjects/ProjectQT/bookings_set.csv");
    for (size_t i = 0; i < bookings.size(); ++i) {
        std::cout << bookings[i] << '\n';
    }

//      Room room = {1, "Deluxe", 2, true, true, false, true, 30.5, 150};
//      std::cout << room;
}