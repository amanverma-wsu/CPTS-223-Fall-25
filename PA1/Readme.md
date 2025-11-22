# Linux Commands Matching Game

**CptS 223: Advanced Data Structures - Programming Assignment 1**

## Overview

This project implements a text-based single-player game to match Linux commands with their correct descriptions. The game uses a custom generic linked list template to store commands and maintains a leaderboard of top players.

## Features

- **Generic Linked List**: Custom implementation with templated Node and List classes
- **Menu-Driven Interface**: 7 different options including gameplay, command management, and leaderboard
- **File I/O**: Reads from and writes to CSV files for persistent data storage
- **Random Quiz Generation**: 20 questions per game with randomized multiple choice answers
- **Leaderboard System**: Tracks top 3 players with persistent storage
- **Input Validation**: Robust error handling for all user inputs

## File Structure

```
├── main.cpp           # Main program entry point with design reflection
├── Game.h             # Game class declaration
├── Game.cpp           # Game class implementation with all functionality
├── List.h             # Generic linked list template
├── Node.h             # Generic node template
├── Command.h          # Command data structure
├── Player.h           # Player data structure
├── Makefile           # Build configuration
├── commands.csv       # Database of Linux commands (50 commands included)
├── leaderboard.csv    # Top 3 players (created after first game)
└── README.md          # This file
```

## Building and Running

### Prerequisites
- C++11 compatible compiler (g++)
- Make utility
- Linux/Unix/Mac environment (or WSL on Windows)

### Build Instructions

```bash
# Build the project
make

# Or use specific targets
make all        # Build everything
make clean      # Remove build artifacts
make rebuild    # Clean and build
make run        # Build and run
make debug      # Build with debug flags
```

### Running the Game

```bash
./linux_game
```

## Game Rules

1. You will be presented with 20 multiple choice questions about Linux commands
2. Each question shows a Linux command and three possible descriptions
3. Choose the correct description by entering 1, 2, or 3
4. Your score will be tracked based on the points assigned to each command
5. After completing all 20 questions, your score will be added to the leaderboard
6. Try to get the highest score and make it to the Top 3!

## Menu Options

1. **View Rules** - Display game instructions
2. **Play a New Game** - Start a 20-question quiz
3. **Add a Command** - Add new Linux commands to the database
4. **Remove a Command** - Remove existing commands from the database
5. **Display All Commands** - Show all commands with descriptions and points
6. **Show Leaderboard** - Display top 3 players and their scores
7. **Save and Exit** - Save all changes and quit the program

## CSV File Formats

### commands.csv
```
command,"description",points
ls,"Lists files and directories in the current folder",2
cd,"Changes the current working directory",2
```

### leaderboard.csv
```
name,points
Alice,45
Bob,38
Charlie,32
```

## Design Decisions

### Linked List vs Array Trade-offs

**Advantage of Linked List:**
- Dynamic memory allocation allows handling variable numbers of commands without pre-declaring a fixed array size
- Provides flexibility when users add or remove commands during runtime

**Disadvantage of Linked List:**
- Random access requires O(n) time complexity since traversal from head is needed
- An array would provide O(1) random access, making question selection more efficient

## Implementation Highlights

- **Generic Templates**: Both Node and List classes are fully templated for reusability
- **Memory Management**: Proper constructors, destructors, copy constructors, and assignment operators
- **Error Handling**: Input validation for all user interactions and file operations
- **Modular Design**: Clean separation between data structures, game logic, and main program
- **CSV Parsing**: Custom parser handles quoted strings and commas within descriptions

## Debugging Support

The project includes comprehensive debugging support:
- Debug build target in Makefile
- Step-through friendly code structure for examining linked list operations
- Clear variable names and function organization for debugger inspection

## Assignment Requirements Met

- ✅ Generic linked list template implementation
- ✅ File I/O with CSV format support
- ✅ Menu-driven text application
- ✅ 20 questions per game with scoring
- ✅ Add/remove command functionality
- ✅ Leaderboard with top 3 players
- ✅ Proper memory management
- ✅ Input validation throughout
- ✅ Makefile for building
- ✅ Design reflection in main.cpp
- ✅ 30+ Linux commands in database

## Sample Gameplay

```
=== Welcome to Linux Commands Matching Game ===

=== MAIN MENU ===
1. View rules
2. Play a new game
3. Add a command
4. Remove a command
5. Display all commands
6. Show leaderboard
7. Save and exit
Enter your choice (1-7): 2

Enter your name: John

=== GAME START ===
Hello John! Let's begin the quiz.

Question 1/20
Command: grep
What does this command do?
1. Creates a new directory
2. Searches text patterns within files
3. Lists USB devices
Your answer (1-3): 2
Correct! +4 points
Current score: 4
```

## Notes

- The game requires at least 20 commands in the database to start playing
- Commands and leaderboard changes are saved only when selecting "Save and exit"
- The program handles edge cases like empty files, invalid CSV formats, and duplicate commands
- All user input is validated with appropriate error messages
