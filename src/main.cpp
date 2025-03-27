#include <iostream>
#include "CANAnalyzer.hpp"

int main() {
    CANAnalyzer analyzer;
    analyzer.simulateMessages();
    analyzer.printStatistics();

    int userID;
    std::cout << "Enter CAN ID to export (in hex, e.g. 0x321): 0x";
    std::cin >> std::hex >> userID;

    analyzer.exportToCSV("filtered_messages.csv", userID);
    return 0;
}
