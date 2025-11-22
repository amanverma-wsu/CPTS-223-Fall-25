#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class Player {
public:
    std::string name;
    int score;

    Player() : name(""), score(0) {}

    Player(const std::string& playerName, int playerScore)
        : name(playerName), score(playerScore) {}

    Player(const Player& other) : name(other.name), score(other.score) {}

    Player& operator=(const Player& other) {
        if (this != &other) {
            name = other.name;
            score = other.score;
        }
        return *this;
    }

    bool operator>(const Player& other) const {
        return score > other.score;
    }

    bool operator<(const Player& other) const {
        return score < other.score;
    }

    friend std::ostream& operator<<(std::ostream& os, const Player& player) {
        os << player.name << ": " << player.score << " points";
        return os;
    }
};

#endif
