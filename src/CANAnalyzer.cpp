#include "CANAnalyzer.hpp"

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

namespace
{
    constexpr int kBaseId = 0x100;
    constexpr int kIdCount = 10;
    constexpr int kBackgroundMessages = 100;
    constexpr double kPeriodSeconds = 0.05;
    constexpr int kSpecialId = 0x321;
    constexpr int kSpecialMessages = 5;
} // namespace

void CANAnalyzer::addMessage(const CANMessage &message)
{
    messages.push_back(message);
}

void CANAnalyzer::simulateMessages()
{
    messages.clear();
    for (int i = 0; i < kBackgroundMessages; ++i)
    {
        int id = kBaseId + (std::rand() % kIdCount);
        std::vector<int> data = {std::rand() % 256, std::rand() % 256};
        double timestamp = i * kPeriodSeconds;

        messages.emplace_back(id, data, timestamp);
    }

    for (int i = 0; i < kSpecialMessages; ++i)
    {
        std::vector<int> data = {std::rand() % 256, std::rand() % 256};
        double timestamp = 5.0 + i * kPeriodSeconds;

        messages.emplace_back(kSpecialId, data, timestamp);
    }
}

std::map<int, int> CANAnalyzer::countByID() const
{
    std::map<int, int> idCount;
    for (const auto &msg : messages)
    {
        ++idCount[msg.id];
    }
    return idCount;
}

void CANAnalyzer::printStatistics() const
{
    std::cout << "Message Statistics by ID (" << messages.size() << " messages):\n";
    for (const auto &entry : countByID())
    {
        std::cout << "ID: 0x" << std::hex << entry.first
                  << " | Count: " << std::dec << entry.second << '\n';
    }
}

int CANAnalyzer::exportToCSV(const std::string &filename, int filterID) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return -1;
    }

    file << "ID,Data1,Data2,Timestamp\n";

    int exported = 0;
    for (const auto &msg : messages)
    {
        if (msg.id != filterID)
            continue;

        file << "0x" << std::hex << msg.id << std::dec << ',';
        if (msg.data.size() > 0)
            file << msg.data[0];
        file << ',';
        if (msg.data.size() > 1)
            file << msg.data[1];
        file << ',' << std::fixed << std::setprecision(2) << msg.timestamp << '\n';
        ++exported;
    }

    return exported;
}

const std::vector<CANMessage> &CANAnalyzer::getMessages() const
{
    return messages;
}
