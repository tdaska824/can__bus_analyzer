# CAN Bus Analyzer (Simulation)

This is a C++ project that simulates a simple CAN bus message analyzer. It generates mock CAN messages, stores them, allows basic filtering, and displays statistics.

## Features
- Add and store CAN messages
- Filter by ID
- Display basic statistics (message count per ID)
- Export to CSV (planned)

## Build & Run
```bash
g++ src/*.cpp -o can_analyzer
./can_analyzer
```

