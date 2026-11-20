#include "Game2048.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include <cctype>
#include <conio.h>
#include <windows.h>

using namespace std;

Game2048::Game2048() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            grid[r][c] = 0;
        }
    }
    bestScore = loadBestScore();
    spawnTile();
    spawnTile();
}

void Game2048::enableAnsiColors() const {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | 0x0004);
}

void Game2048::run() {
    enableAnsiColors();
    cout << "\033[2J\033[H";
    printGrid();

    while (true) {
        if (isGameOver()) {
            cout << "\nGame Over! Punteggio Finale: " << score << endl;
            break;
        }

        char input = static_cast<char>(tolower(_getch()));

        if (input == 'q') break;

        bool moved = false;

        if (input == 'w') moved = moveUp();
        else if (input == 's') moved = moveDown();
        else if (input == 'a') moved = moveLeft();
        else if (input == 'd') moved = moveRight();

        if (moved) {
            if (score > bestScore) {
                bestScore = score;
                saveBestScore();
            }
            spawnTile();
            cout << "\033[2J\033[H";
            printGrid();
        }

    }
}

string Game2048::getTileColor(int val) const {
    switch (val) {
        case 2: return "\033[97m";
        case 4: return "\033[93m";
        case 8: return "\033[33m";
        case 16: return "\033[91m";
        case 32: return "\033[31m";
        case 64: return "\033[95m";
        case 128: return "\033[96m";
        case 256: return "\033[36m";
        case 512: return "\033[92m";
        case 1024: return "\033[1;94m";
        case 2048: return "\033[1;93m";
        default: return "\033[90m";
    }
}

void Game2048::printGrid() const{
    cout << "SCORE: " << score << "     BEST: " << bestScore << endl << endl;
    cout << "+------+------+------+------+" << endl;

    for (int r = 0; r < 4; r++) {
        cout << "|";
        for (int c = 0; c < 4; c++) {
            int val = grid[r][c];
            cout << getTileColor(val);

            if (val == 0) cout << "   .  ";
            else cout << setw(5) << val << " ";
            cout << "\33[0m|";
        }

        cout << endl << "+------+------+------+------+" << endl;
    }
}

void Game2048::spawnTile() {

    static mt19937 gen(
        random_device{}() ^ chrono::steady_clock::now().time_since_epoch().count()
    );

    vector<int> emptyRows;
    vector<int> emptyCols;

    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (grid[r][c] == 0) {
                emptyRows.push_back(r);
                emptyCols.push_back(c);
            }
        }
    }

    if (emptyRows.empty()) return;

    uniform_int_distribution<int> posDist(0, emptyRows.size() - 1);
    int index = posDist(gen);
    int r = emptyRows[index];
    int c = emptyCols[index];

    uniform_int_distribution<int> valDist(1,10);
    if (valDist(gen) == 1) grid[r][c] = 4;
    else grid[r][c] = 2;
}

bool Game2048::slideRowLeft(int row[4]) {
    int original[4] = { row[0], row[1], row[2], row[3] };
    int temp[4] = {0};
    int pos = 0;

    for (int i = 0; i < 4; i++) {
        if (row[i] != 0) {
            temp[pos] = row[i];
            pos++;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (temp[i] != 0 && temp[i] == temp[i + 1]) {
            temp[i] *= 2;
            score += temp[i];
            temp[i + 1] = 0;
            i++;
        }
    }

    row[0] = row[1] = row[2] = row[3] = 0;
    pos = 0;
    for (int i = 0; i < 4; i++) {
        if (temp[i] != 0) {
            row[pos] = temp[i];
            pos++;
        }
    }

    for (int i = 0; i < 4; i++) {
        if (row[i] != original[i]) return true;
    }
    return false;
}

bool Game2048::moveLeft() {
    bool moved = false;
    for (int r = 0; r < 4; r++) {
        if (slideRowLeft(grid[r])) {
            moved = true;
        }
    }
    return moved;
}

bool Game2048::moveRight() {
    bool moved = false;
    for (int r = 0; r < 4; r++) {
        int row[4] = {grid[r][3], grid[r][2], grid[r][1], grid[r][0]};

        if (slideRowLeft(row)) {
            moved = true;
        }
        grid[r][3] = row[0];
        grid[r][2] = row[1];
        grid[r][1] = row[2];
        grid[r][0] = row[3];
    }
    return moved;
}

bool Game2048::moveUp() {
    bool moved = false;
    for (int c = 0; c < 4; c++) {
        int col[4] = {grid[0][c], grid[1][c], grid[2][c], grid[3][c]};

        if (slideRowLeft(col)) {
            moved = true;
        }
        grid[0][c] = col[0];
        grid[1][c] = col[1];
        grid[2][c] = col[2];
        grid[3][c] = col[3];
    }
    return moved;
}

bool Game2048::moveDown() {
    bool moved = false;
    for (int c = 0; c < 4; c++) {
        int col[4] = {grid[3][c], grid[2][c], grid[1][c], grid[0][c]};

        if (slideRowLeft(col)) {
            moved = true;
        }

        grid[3][c] = col[0];
        grid[2][c] = col[1];
        grid[1][c] = col[2];
        grid[0][c] = col[3];
    }
    return moved;
}

bool Game2048::isGameOver() {
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            if (grid[r][c] == 0) return false;

            if (c < 3 && grid[r][c] == grid[r][c+1]) return false;

            if (r < 3 && grid[r][c] == grid[r + 1][c]) return false;
        }
    }
    return true;
}

int Game2048::loadBestScore() const{
    ifstream file("highscore.txt");
    int best = 0;
    if (file.is_open()) {
        file >> best;
        file.close();
    }
    return best;
}

void Game2048::saveBestScore() const{
    ofstream file("highscore.txt");
    if (file.is_open()) {
        file << bestScore;
        file.close();
    }
}