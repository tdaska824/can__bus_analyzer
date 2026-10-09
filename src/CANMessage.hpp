#ifndef CANMESSAGE_HPP
#define CANMESSAGE_HPP

#include <vector>

struct CANMessage
{
    int id; // 11-bit identifier
    std::vector<int> data;
    double timestamp; // time in seconds since the start of the capture

    CANMessage(int id, const std::vector<int> &data, double timestamp);
};

#endif
