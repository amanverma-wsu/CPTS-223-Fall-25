#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>
#include <iomanip>

Game::Game() {
    loadCommands();
    loadLeaderboard();
}

Game::~Game() {
}

void Game::run() {
    int choice;
    bool running = true;

    std::cout << "=== Welcome to Linux Commands Matching Game ===" << std::endl;
    std::cout << std::endl;

    while (running) {
        displayMenu();
        choice = getValidMenuChoice();

        switch (choice) {
            case 1:
                viewRules();
                break;
            case 2:
                playNewGame();
                break;
            case 3:
                addCommand();
                break;
            case 4:
                removeCommand();
                break;
            case 5:
                displayAllCommands();
                break;
            case 6:
                showLeaderboard();
                break;
            case 7:
                saveAndExit();
                running = false;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        
        if (running) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            std::cout << std::endl;
        }
    }
}

void Game::displayMenu() {
    std::cout << "=== MAIN MENU ===" << std::endl;
    std::cout << "1. View rules" << std::endl;
    std::cout << "2. Play a new game" << std::endl;
    std::cout << "3. Add a command" << std::endl;
    std::cout << "4. Remove a command" << std::endl;
    std::cout << "5. Display all commands" << std::endl;
    std::cout << "6. Show leaderboard" << std::endl;
    std::cout << "7. Save and exit" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

int Game::getValidMenuChoice() {
    int choice;
    while (!(std::cin >> choice) || choice < 1 || choice > 7) {
        std::cout << "Invalid input. Please enter a number between 1 and 7: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore();
    return choice;
}

void Game::viewRules() {
    displayRules();
}

void Game::displayRules() {
    std::cout << "\n=== GAME RULES ===" << std::endl;
    std::cout << "1. You will be presented with 20 multiple choice questions about Linux commands." << std::endl;
    std::cout << "2. Each question shows a Linux command and three possible descriptions." << std::endl;
    std::cout << "3. Choose the correct description by entering 1, 2, or 3." << std::endl;
    std::cout << "4. Your score will be tracked based on the points assigned to each command." << std::endl;
    std::cout << "5. After completing all 20 questions, your score will be added to the leaderboard." << std::endl;
    std::cout << "6. Try to get the highest score and make it to the Top 3!" << std::endl;
    std::cout << std::endl;
}

void Game::playNewGame() {
    if (commands.getSize() < QUESTIONS_PER_GAME) {
        std::cout << "Not enough commands in the database. Need at least " 
                  << QUESTIONS_PER_GAME << " commands to play." << std::endl;
        return;
    }

    std::string playerName;
    std::cout << "Enter your name: ";
    std::getline(std::cin, playerName);
    
    if (playerName.empty()) {
        std::cout << "Invalid name. Game cancelled." << std::endl;
        return;
    }

    int score = 0;
    std::vector<int> questionIndices = generateRandomQuestions();

    std::cout << "\n=== GAME START ===" << std::endl;
    std::cout << "Hello " << playerName << "! Let's begin the quiz." << std::endl;
    std::cout << std::endl;

    for (int i = 0; i < QUESTIONS_PER_GAME; i++) {
        const Command& currentCommand = commands.at(questionIndices[i]);
        std::vector<std::string> choices = generateChoices(currentCommand);

        std::cout << "Question " << (i + 1) << "/" << QUESTIONS_PER_GAME << std::endl;
        std::cout << "Command: " << currentCommand.command << std::endl;
        std::cout << "What does this command do?" << std::endl;
        
        for (int j = 0; j < 3; j++) {
            std::cout << (j + 1) << ". " << choices[j] << std::endl;
        }

        int answer;
        std::cout << "Your answer (1-3): ";
        while (!(std::cin >> answer) || answer < 1 || answer > 3) {
            std::cout << "Invalid input. Please enter 1, 2, or 3: ";
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        }

        if (choices[answer - 1] == currentCommand.description) {
            std::cout << "Correct! +" << currentCommand.points << " points" << std::endl;
            score += currentCommand.points;
        } else {
            std::cout << "Wrong! The correct answer was: " << currentCommand.description << std::endl;
        }
        std::cout << "Current score: " << score << std::endl;
        std::cout << std::endl;
    }

    std::cout << "=== GAME OVER ===" << std::endl;
    std::cout << playerName << ", your final score is: " << score << " points" << std::endl;

    Player newPlayer(playerName, score);
    updateLeaderboard(newPlayer);

    std::cout << "Your score has been added to the leaderboard!" << std::endl;
}

std::vector<int> Game::generateRandomQuestions() {
    std::vector<int> indices;
    for (int i = 0; i < commands.getSize(); i++) {
        indices.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(indices.begin(), indices.end(), gen);

    return std::vector<int>(indices.begin(), indices.begin() + QUESTIONS_PER_GAME);
}

std::vector<std::string> Game::generateChoices(const Command& correctCommand) {
    std::vector<std::string> choices;
    choices.push_back(correctCommand.description);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, commands.getSize() - 1);

    while (choices.size() < 3) {
        int randomIndex = dis(gen);
        const Command& randomCommand = commands.at(randomIndex);
        
        if (randomCommand.description != correctCommand.description &&
            std::find(choices.begin(), choices.end(), randomCommand.description) == choices.end()) {
            choices.push_back(randomCommand.description);
        }
    }

    std::shuffle(choices.begin(), choices.end(), gen);
    return choices;
}

void Game::addCommand() {
    std::string command, description;
    int points;

    std::cout << "Enter the command: ";
    std::getline(std::cin, command);
    command = trim(command);

    if (command.empty()) {
        std::cout << "Invalid command. Operation cancelled." << std::endl;
        return;
    }

    Command tempCommand(command, "", 0);
    if (commands.find(tempCommand)) {
        std::cout << "Warning: Command '" << command << "' already exists!" << std::endl;
        return;
    }

    std::cout << "Enter the description: ";
    std::getline(std::cin, description);
    description = trim(description);

    if (description.empty()) {
        std::cout << "Invalid description. Operation cancelled." << std::endl;
        return;
    }

    std::cout << "Enter the points: ";
    while (!(std::cin >> points) || points < 1) {
        std::cout << "Invalid points. Please enter a positive number: ";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
    }
    std::cin.ignore();

    Command newCommand(command, description, points);
    commands.insertBack(newCommand);

    std::cout << "Command added successfully! (Will be saved on exit)" << std::endl;
}

void Game::removeCommand() {
    std::string command;
    std::cout << "Enter the command to remove: ";
    std::getline(std::cin, command);
    command = trim(command);

    if (command.empty()) {
        std::cout << "Invalid command. Operation cancelled." << std::endl;
        return;
    }

    Command tempCommand(command, "", 0);
    if (commands.remove(tempCommand)) {
        std::cout << "Command removed successfully! (Will be saved on exit)" << std::endl;
    } else {
        std::cout << "Warning: Command '" << command << "' not found!" << std::endl;
    }
}

void Game::displayAllCommands() {
    if (commands.isEmpty()) {
        std::cout << "No commands in the database." << std::endl;
        return;
    }

    std::cout << "\n=== ALL COMMANDS ===" << std::endl;
    std::cout << std::setw(15) << "Command" << " | " 
              << std::setw(50) << "Description" << " | " 
              << "Points" << std::endl;
    std::cout << std::string(75, '-') << std::endl;

    for (int i = 0; i < commands.getSize(); i++) {
        const Command& cmd = commands.at(i);
        std::cout << std::setw(15) << cmd.command << " | " 
                  << std::setw(50) << cmd.description.substr(0, 50) << " | " 
                  << cmd.points << std::endl;
    }
    std::cout << "\nTotal commands: " << commands.getSize() << std::endl;
}

void Game::showLeaderboard() {
    std::cout << "\n=== LEADERBOARD (TOP 3) ===" << std::endl;
    
    if (leaderboard.empty()) {
        std::cout << "No players yet. Be the first to play!" << std::endl;
        return;
    }

    for (size_t i = 0; i < leaderboard.size(); i++) {
        std::cout << (i + 1) << ". " << leaderboard[i] << std::endl;
    }
}

void Game::updateLeaderboard(const Player& newPlayer) {
    auto insertPos = leaderboard.begin();
    for (auto it = leaderboard.begin(); it != leaderboard.end(); ++it) {
        if (newPlayer.score > it->score) {
            insertPos = it;
            break;
        }
        insertPos = it + 1;
    }

    leaderboard.insert(insertPos, newPlayer);

    if (leaderboard.size() > MAX_LEADERBOARD_SIZE) {
        leaderboard.resize(MAX_LEADERBOARD_SIZE);
    }
}

void Game::saveAndExit() {
    std::cout << "Saving data..." << std::endl;
    
    bool commandsSaved = saveCommands();
    bool leaderboardSaved = saveLeaderboard();

    if (commandsSaved && leaderboardSaved) {
        std::cout << "All data saved successfully!" << std::endl;
    } else {
        std::cout << "Warning: Some data may not have been saved properly." << std::endl;
    }

    std::cout << "Thank you for playing! Goodbye!" << std::endl;
}

bool Game::loadCommands() {
    std::ifstream file("commands.csv");
    if (!file.is_open()) {
        std::cout << "commands.csv not found. Please create the file with Linux commands." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> tokens = parseCSVLine(line);
        if (tokens.size() >= 3) {
            std::string command = trim(tokens[0]);
            std::string description = trim(tokens[1]);
            int points = std::stoi(trim(tokens[2]));

            Command cmd(command, description, points);
            commands.insertBack(cmd);
        }
    }

    file.close();
    return true;
}

bool Game::saveCommands() {
    std::ofstream file("commands.csv");
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < commands.getSize(); i++) {
        const Command& cmd = commands.at(i);
        file << cmd.command << ",\"" << cmd.description << "\"," << cmd.points << std::endl;
    }

    file.close();
    return true;
}

bool Game::loadLeaderboard() {
    std::ifstream file("leaderboard.csv");
    if (!file.is_open()) {
        return true;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::vector<std::string> tokens = parseCSVLine(line);
        if (tokens.size() >= 2) {
            std::string name = trim(tokens[0]);
            int score = std::stoi(trim(tokens[1]));

            Player player(name, score);
            leaderboard.push_back(player);
        }
    }

    file.close();
    
    std::sort(leaderboard.begin(), leaderboard.end(), 
              [](const Player& a, const Player& b) { return a.score > b.score; });
    
    if (leaderboard.size() > MAX_LEADERBOARD_SIZE) {
        leaderboard.resize(MAX_LEADERBOARD_SIZE);
    }

    return true;
}

bool Game::saveLeaderboard() {
    std::ofstream file("leaderboard.csv");
    if (!file.is_open()) {
        return false;
    }

    for (const Player& player : leaderboard) {
        file << player.name << "," << player.score << std::endl;
    }

    file.close();
    return true;
}

std::string Game::trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n\"");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\r\n\"");
    return str.substr(start, end - start + 1);
}

std::vector<std::string> Game::parseCSVLine(const std::string& line) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    bool inQuotes = false;
    std::string current = "";

    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            tokens.push_back(current);
            current = "";
        } else {
            current += c;
        }
    }
    tokens.push_back(current);

    return tokens;
}

