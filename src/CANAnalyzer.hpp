#ifndef CANANALYZER_HPP
#define CANANALYZER_HPP

#include "CANMessage.hpp"
#include <vector>
#include <unordered_map>
#include <string>

class CANAnalyzer {
public:
    void simulateMessages();
    void printStatistics();
    void exportToCSV(const std::string& filename, int filterID);

private:
    std::vector<CANMessage> messages;
};

#endif
