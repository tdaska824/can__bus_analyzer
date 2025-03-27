#ifndef CANMESSAGE_HPP
#define CANMESSAGE_HPP

#include <vector>
#include <string>

struct CANMessage {
    int id;
    std::vector<int> data;
    double timestamp;

    CANMessage(int id, const std::vector<int>& data, double timestamp);
};

#endif
