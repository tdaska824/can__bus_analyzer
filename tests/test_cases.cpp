#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "CANAnalyzer.hpp"

static int failures = 0;

#define CHECK(condition)                                                       \
    do                                                                         \
    {                                                                          \
        if (!(condition))                                                      \
        {                                                                      \
            std::cerr << "FAILED: " #condition " (line " << __LINE__ << ")\n"; \
            ++failures;                                                        \
        }                                                                      \
    } while (0)

static std::vector<std::string> readLines(const std::string &path)
{
    std::ifstream in(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line))
        lines.push_back(line);
    return lines;
}

static void testSimulationSize()
{
    CANAnalyzer analyzer;
    analyzer.simulateMessages();
    CHECK(analyzer.getMessages().size() == 105);

    analyzer.simulateMessages();
    CHECK(analyzer.getMessages().size() == 105);
}

static void testCountByID()
{
    CANAnalyzer analyzer;
    analyzer.simulateMessages();

    std::map<int, int> counts = analyzer.countByID();
    CHECK(counts[0x321] == 5);

    int total = 0;
    for (const auto &entry : counts)
        total += entry.second;
    CHECK(total == 105);

    for (const auto &entry : counts)
    {
        bool known = (entry.first >= 0x100 && entry.first <= 0x109) || entry.first == 0x321;
        CHECK(known);
    }
}

static void testExportFilter()
{
    const std::string path = "test_output.csv";
    CANAnalyzer analyzer;
    analyzer.addMessage(CANMessage(0x321, {10, 20}, 1.0));
    analyzer.addMessage(CANMessage(0x100, {1, 2}, 1.05));
    analyzer.addMessage(CANMessage(0x321, {30, 40}, 1.10));

    int exported = analyzer.exportToCSV(path, 0x321);
    CHECK(exported == 2);

    std::vector<std::string> lines = readLines(path);
    CHECK(lines.size() == 3);
    if (lines.size() == 3)
    {
        CHECK(lines[0] == "ID,Data1,Data2,Timestamp");
        CHECK(lines[1] == "0x321,10,20,1.00");
        CHECK(lines[2] == "0x321,30,40,1.10");
    }
    std::remove(path.c_str());
}

static void testExportUnknownID()
{
    const std::string path = "test_output_empty.csv";
    CANAnalyzer analyzer;
    analyzer.simulateMessages();

    CHECK(analyzer.exportToCSV(path, 0x7FF) == 0);
    CHECK(readLines(path).size() == 1);
    std::remove(path.c_str());
}

static void testShortPayload()
{
    const std::string path = "test_output_short.csv";
    CANAnalyzer analyzer;
    analyzer.addMessage(CANMessage(0x200, {7}, 2.0));

    CHECK(analyzer.exportToCSV(path, 0x200) == 1);
    std::vector<std::string> lines = readLines(path);
    CHECK(lines.size() == 2);
    if (lines.size() == 2)
        CHECK(lines[1] == "0x200,7,,2.00");
    std::remove(path.c_str());
}

static void testBadPath()
{
    CANAnalyzer analyzer;
    analyzer.simulateMessages();
    CHECK(analyzer.exportToCSV("no_such_folder/out.csv", 0x321) == -1);
}

int main()
{
    testSimulationSize();
    testCountByID();
    testExportFilter();
    testExportUnknownID();
    testShortPayload();
    testBadPath();

    if (failures == 0)
    {
        std::cout << "All tests passed." << std::endl;
        return 0;
    }
    std::cout << failures << " check(s) failed." << std::endl;
    return 1;
}
