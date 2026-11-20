//
// Created by diego on 20/11/2026.
//

#ifndef CPP_2048_GAME2048_H
#define CPP_2048_GAME2048_H

#include <string>

class Game2048 {
private:
    int grid[4][4] {};
    int score = 0;
    int bestScore = 0;

    void enableAnsiColors() const;
    std::string getTileColor(int val) const;
    void printGrid() const;
    void spawnTile();

    bool slideRowLeft(int row[4]);
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    bool isGameOver();

    int loadBestScore() const;
    void saveBestScore() const;
public:
    Game2048();
    void run();
};

#endif //CPP_2048_GAME2048_H
