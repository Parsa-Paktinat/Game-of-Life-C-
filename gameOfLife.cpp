#include <iostream>
#include <chrono>
#include <thread>

const unsigned int row = 30;
const unsigned int column = 40;

void generateRandomMap(char map[row][column]) {
    srand((unsigned) time(nullptr));

    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++) {
            if (static_cast<int>(rand()) % 7 != 0)
                map[i][j] = ' ';
            else
                map[i][j] = '#';
        }
}

void copyMap(char map[row][column], char copiedMap[row][column]) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            copiedMap[i][j] = map[i][j];
}

void generateNewMap(char map[row][column]) {
    char copiedMap[row][column];
    copyMap(map, copiedMap);

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            int lives = 0;
            for (int id = -1; id <= 1; id++)
                for (int jd = -1; jd <= 1; jd++)
                    if (map[(id+i)%row][(jd+j)%column] == '#')
                        lives++;

            if (map[i][j] == '#') 
                lives--;

            copiedMap[i][j] = (lives == 3 || (lives == 2 && map[i][j] == '#')) ? '#' : ' ';
        }
    }

    copyMap(copiedMap, map);
}

void drawMap(char map[row][column]) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++)
            std::cout << map[i][j];
        std::cout << std::endl;
    }
}

int main() {
    char map[row][column];
    generateRandomMap(map);

    while (true) {
        drawMap(map);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        system("cls");
        generateNewMap(map);
    }

    return 0;
}