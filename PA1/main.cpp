/*
 * Programming Assignment 1 - Linux Commands Matching Game
 * CptS 223: Advanced Data Structures
*/

#include "Game.h"
#include <iostream>

int main() {
    try {
        Game linuxGame;
        linuxGame.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
