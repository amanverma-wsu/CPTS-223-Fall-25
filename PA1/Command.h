#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <iostream>

class Command {
public:
    std::string command;
    std::string description;
    int points;

    Command() : command(""), description(""), points(0) {}

    
    Command(const std::string& cmd, const std::string& desc, int pts)
        : command(cmd), description(desc), points(pts) {}

    
    Command(const Command& other) 
        : command(other.command), description(other.description), points(other.points) {}

    
    Command& operator=(const Command& other) {
        if (this != &other) {
            command = other.command;
            description = other.description;
            points = other.points;
        }
        return *this;
    }

    
    bool operator==(const Command& other) const {
        return command == other.command;
    }

    
    friend std::ostream& operator<<(std::ostream& os, const Command& cmd) {
        os << "Command: " << cmd.command << "\n"
           << "Description: " << cmd.description << "\n"
           << "Points: " << cmd.points;
        return os;
    }
};

#endif // COMMAND_H
