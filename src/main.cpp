#include <cstdlib>
#include <ctime>
#include <iostream>
#include "CANAnalyzer.hpp"

int main()
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    CANAnalyzer analyzer;
    analyzer.simulateMessages();
    analyzer.printStatistics();

    int userID = 0;
    std::cout << "\nEnter CAN ID to export (in hex, e.g. 321): 0x";
    if (!(std::cin >> std::hex >> userID))
    {
        std::cerr << "Invalid ID. Please enter a hexadecimal number such as 321." << std::endl;
        return 1;
    }

    const std::string filename = "filtered_messages.csv";
    int exported = analyzer.exportToCSV(filename, userID);
    if (exported < 0)
    {
        return 1;
    }

    std::cout << exported << " message(s) with ID 0x" << std::hex << userID << std::dec
              << " exported to " << filename << std::endl;
    if (exported == 0)
    {
        std::cout << "No messages with that ID were found." << std::endl;
    }
    return 0;
}
