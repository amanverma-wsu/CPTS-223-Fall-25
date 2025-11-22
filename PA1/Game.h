#ifndef GAME_H
#define GAME_H

#include "List.h"
#include "Command.h"
#include "Player.h"
#include <vector>
#include <string>

class Game {
private:
    List<Command> commands;
    std::vector<Player> leaderboard;
    static const int MAX_LEADERBOARD_SIZE = 3;
    static const int QUESTIONS_PER_GAME = 20;

    bool loadCommands();
    bool saveCommands();
    bool loadLeaderboard();
    bool saveLeaderboard();
    void updateLeaderboard(const Player& newPlayer);
    std::vector<int> generateRandomQuestions();
    std::vector<std::string> generateChoices(const Command& correctCommand);
    void displayRules();
    void displayMenu();
    int getValidMenuChoice();
    std::string trim(const std::string& str);
    std::vector<std::string> parseCSVLine(const std::string& line);

public:
    Game();
    ~Game();

    void run();
    void viewRules();
    void playNewGame();
    void addCommand();
    void removeCommand();
    void displayAllCommands();
    void showLeaderboard();
    void saveAndExit();
};

#endif
