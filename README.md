# 2048 CLI — C++

A terminal-based implementation of the classic **2048** puzzle game written in modern C++ using Object-Oriented Design, ANSI escape sequences for color rendering, and persistent local high-score storage.

## Features
- **Clean OOP Architecture:** Game logic, rendering, and state management encapsulated in a modular `Game2048` class (`Game2048.h` / `Game2048.cpp`).
- **Real-Time Terminal Controls:** Non-blocking keyboard input (`W/A/S/D` to move, `Q` to quit) with flicker-free ANSI screen updates.
- **Color-Coded Tiles:** Distinct ANSI color palette for each power of 2 up to `2048`.
- **Persistent High Score:** Automatically loads and updates the best score locally via `highscore.txt`.
- **Unbiased RNG:** Uses `std::mt19937` seeded with `std::random_device` and `std::chrono` for tile spawning (`90%` chance for `2`, `10%` for `4`).

## Project Structure
```text
cpp-2048/
├── CMakeLists.txt
├── Game2048.h      # Class declaration and private state
├── Game2048.cpp    # Game mechanics, rendering, and file I/O
├── main.cpp        # Entry point
└── README.md
