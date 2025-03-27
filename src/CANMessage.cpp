#include "CANMessage.hpp"

CANMessage::CANMessage(int id, const std::vector<int>& data, double timestamp)
    : id(id), data(data), timestamp(timestamp) {}
