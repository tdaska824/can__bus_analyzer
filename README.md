# CAN Bus Analyzer (Simulation)

A small C++ project that simulates a CAN bus message analyzer. It generates mock CAN frames, stores them in memory, prints how many frames each ID sent, and exports the frames of one chosen ID to a CSV file.

It is a learning project for the software side of CAN: identifiers, payload bytes, timestamps, traffic statistics and filtering, without needing any hardware.

## CAN in one minute

Controller Area Network (CAN) is a multi-node serial bus used in cars and embedded systems. Every node broadcasts frames, and each frame carries:

| Field | Meaning |
|-------|---------|
| ID | Identifies the message type and sets its priority (lower ID wins arbitration) |
| DLC | Number of data bytes in the frame (0-8 for classic CAN) |
| Data | The payload, for example a sensor reading |

An analyzer sits on the bus, records the frames, and shows which messages are sent and how often.

## Features

- Simulates 105 frames: 100 frames with random IDs `0x100`-`0x109` every 50 ms, then 5 frames with ID `0x321`. Each frame has 2 random data bytes.
- Stores the frames as `CANMessage` objects (ID, data bytes, timestamp)
- Prints the message count per ID, sorted by ID
- Exports all frames with a chosen ID to `filtered_messages.csv`
- Handles invalid input and IDs that do not exist
- Includes tests for the analyzer logic

## Project structure

```
can__bus_analyzer/
├── src/
│   ├── main.cpp              # entry point: simulate, print statistics, ask for an ID, export
│   ├── CANMessage.hpp/.cpp   # one CAN frame (ID, data bytes, timestamp)
│   └── CANAnalyzer.hpp/.cpp  # frame storage, simulation, statistics, CSV export
├── tests/
│   └── test_cases.cpp        # tests (no external framework)
├── .gitignore
└── README.md
```

## Build and run

Requires a C++ compiler with C++11 support or newer (tested with `g++` and `-std=c++17`).

```bash
g++ -std=c++17 -Wall -Wextra src/*.cpp -o can_analyzer
./can_analyzer          # on Windows PowerShell: .\can_analyzer.exe
```

The program prints the statistics, then asks for a CAN ID in hexadecimal. Type `321` (the `0x` prefix is already shown) and press Enter. The result is written to `filtered_messages.csv` in the current folder.

### Example run

The counts differ on every run because the traffic is random.

```
Message Statistics by ID (105 messages):
ID: 0x100 | Count: 10
ID: 0x101 | Count: 7
ID: 0x102 | Count: 9
ID: 0x103 | Count: 5
ID: 0x104 | Count: 15
ID: 0x105 | Count: 8
ID: 0x106 | Count: 13
ID: 0x107 | Count: 15
ID: 0x108 | Count: 8
ID: 0x109 | Count: 10
ID: 0x321 | Count: 5

Enter CAN ID to export (in hex, e.g. 321): 0x321
5 message(s) with ID 0x321 exported to filtered_messages.csv
```

`filtered_messages.csv`:

```
ID,Data1,Data2,Timestamp
0x321,85,45,5.00
0x321,39,145,5.05
0x321,208,229,5.10
0x321,41,119,5.15
0x321,146,195,5.20
```

## Tests

The tests use a small `CHECK` macro, so no extra library is needed. From the repository root:

```bash
g++ -std=c++17 -Wall -Wextra -Isrc tests/test_cases.cpp src/CANAnalyzer.cpp src/CANMessage.cpp -o test_runner
./test_runner           # on Windows PowerShell: .\test_runner.exe
```

Expected output: `All tests passed.` (plus one error line about `no_such_folder/out.csv`, which is the "bad path" test checking that a failed export is reported.)

What the tests cover:

- the simulation creates 105 messages, and calling it twice does not duplicate them
- the per-ID counts add up to 105, and ID `0x321` appears 5 times
- the CSV export keeps only the requested ID and writes the exact expected rows
- exporting an ID that does not exist writes only the header
- a frame with a single data byte is exported with an empty second column
- exporting to an invalid path returns an error

## Roadmap

- [ ] Message rate (frames per second) per ID
- [ ] Support for extended 29-bit identifiers and payloads up to 8 bytes
- [ ] Read frames from a real interface (for example SocketCAN) instead of mock data
- [ ] Decode payloads into signals (scaling, offset, units)

## Author

Theopoula Eirini Daskalou, Computer Science, Aristotle University of Thessaloniki
[LinkedIn](https://www.linkedin.com/in/thei-daskalou-3567a8358) | [GitHub](https://github.com/tdaska824)
