# 2048 CLI — C++20

A terminal-based implementation of the classic **2048** puzzle game built from scratch in **C++20**. Designed with clean Object-Oriented principles, ANSI escape sequences for color-coded rendering, and persistent local high-score tracking.

## Features
- **Modular OOP Architecture:** Game state, input handling, and rendering are encapsulated within the `Game2048` class (`Game2048.h` / `Game2048.cpp`), keeping `main.cpp` minimal.
- **Responsive CLI Controls:** Instant, non-blocking keyboard input (`W/A/S/D` to move, `Q` to quit) without requiring the `Enter` key.
- **ANSI Color Rendering:** Distinct color palette for each tile value from `2` up to `2048`, paired with flicker-free screen updates.
- **Persistent High Score:** Automatically loads and saves the all-time best score locally in `highscore.txt`.
- **Unbiased Tile Spawning:** Uses `std::mt19937` seeded via `std::random_device` and `std::chrono` (`90%` chance for `2`, `10%` for `4`).

## Project Structure
```text
cpp-2048/
├── CMakeLists.txt
├── Game2048.h      # Class interface and private game state
├── Game2048.cpp    # Movement logic, tile merging, rendering, and file I/O
├── main.cpp        # Application entry point
└── README.md
```

## Build & Run (Windows)

### Option 1: Using CMake (Recommended)
```bash
cmake -B build
cmake --build build
.\build\cpp_2048.exe
```

### Option 2: Using g++ directly
```bash
g++ -std=c++20 main.cpp Game2048.cpp -o cpp_2048.exe
.\cpp_2048.exe
```

## Controls
| Key | Action |
| :--- | :--- |
| `W` | Slide Tiles Up |
| `A` | Slide Tiles Left |
| `S` | Slide Tiles Down |
| `D` | Slide Tiles Right |
| `Q` | Quit Game |

## Implementation Highlights
- **Single-Pass Merge Logic:** All four directional movements reuse a single `slideRowLeft()` helper by extracting and re-inserting rows or columns in the target direction, preventing duplicate code and double-merging within the same turn.
- **Windows Console Compatibility:** Enables `ENABLE_VIRTUAL_TERMINAL_PROCESSING` (`0x0004`) via the Windows Console API (`SetConsoleMode`) so ANSI escape codes render natively in Windows Terminal and PowerShell.
