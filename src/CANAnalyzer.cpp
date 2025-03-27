#include "CANAnalyzer.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>

void CANAnalyzer::simulateMessages() {
    std::srand(std::time(nullptr));

    for (int i = 0; i < 100; ++i) {
        int id = 0x100 + (std::rand() % 10); // ids μεταξύ 0x100 και 0x109
        std::vector<int> data = { std::rand() % 256, std::rand() % 256 };
        double timestamp = i * 0.05; // simulate 50ms intervals

        messages.emplace_back(id, data, timestamp);
    }

    // Προσθέτουμε και μερικά μηνύματα με ID 0x321
    for (int i = 0; i < 5; ++i) {
        std::vector<int> data = { std::rand() % 256, std::rand() % 256 };
        double timestamp = 5.0 + i * 0.05;
        messages.emplace_back(0x321, data, timestamp);
    }
}

void CANAnalyzer::printStatistics() {
    std::unordered_map<int, int> idCount;

    for (const auto& msg : messages) {
        idCount[msg.id]++;
    }

    std::cout << "Message Statistics by ID:" << std::endl;
    for (const auto& pair : idCount) {
        std::cout << "ID: 0x" << std::hex << pair.first
                  << " | Count: " << std::dec << pair.second << std::endl;
    }
}

void CANAnalyzer::exportToCSV(const std::string& filename, int filterID) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    file << "ID,Data1,Data2,Timestamp\n";
    for (const auto& msg : messages) {
        if (msg.id != filterID) continue;  // Φίλτρο: μόνο ID που δίνει ο χρήστης

        file << "0x" << std::hex << msg.id << ","
             << std::dec << msg.data[0] << ","
             << msg.data[1] << ","
             << std::fixed << std::setprecision(2) << msg.timestamp << "\n";
    }

    file.close();
    std::cout << "Filtered messages (ID = 0x" << std::hex << filterID << ") exported to " << filename << std::endl;
}
