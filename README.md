# CAN Bus Analyzer (Simulation)

A simple C++ project that simulates a basic CAN bus message analyzer.  
It generates mock CAN messages, allows filtering by message ID, and exports filtered results to a CSV file.

---

## Features

- Generate random CAN messages with ID, data bytes, and timestamps
- Add manual messages with a specific ID (e.g. `0x321`)
- Filter and export messages by ID
- Export filtered messages to `filtered_messages.csv`
- Console statistics (message count per ID)

---

## Compile & Run (Windows - MSYS2)

### Compile
```bash
g++ -o can_analyzer main.cpp CANAnalyzer.cpp CANMessage.cpp

