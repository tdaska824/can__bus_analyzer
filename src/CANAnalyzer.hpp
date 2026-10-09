#ifndef CANANALYZER_HPP
#define CANANALYZER_HPP

#include <map>
#include <string>
#include <vector>
#include "CANMessage.hpp"

class CANAnalyzer
{
public:
    void addMessage(const CANMessage &message);

    void simulateMessages();

    std::map<int, int> countByID() const;

    void printStatistics() const;

    int exportToCSV(const std::string &filename, int filterID) const;

    const std::vector<CANMessage> &getMessages() const;

private:
    std::vector<CANMessage> messages;
};

#endif
