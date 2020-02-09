/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author ( Fill with your own info )
 * Name: Nguyen The Anh
 * Student number: 292126
 * UserID: cxanng
 * E-Mail: anh.t.nguyen@tuni.fi
 *
 * Notes about the program and it's implementation:
 *
 * */

#include "board.hh"
#include <string>
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>

const int EMPTY = 16;

// Check if the first command to choose random initialization or not is correct,
// it asks for the command until users type in the right commands
std::string check_initial_command(std::string& command) {
    while (command !="y" && command !="Y" && command != "n" && command != "N" )
    {
        std::cout << "Unknown choice: " << command << std::endl;
        std::cout << "Random initialization (y/n): " ;
        getline(std::cin, command);
    }
    return command;
}

// Check if the moving commands are typed in correctly, there are only four options
// is "a", "s", "d", "w", and then return a true/ false value
bool check_moving_command(std::string command) {
    if (command != "a" && command != "s" && command != "d" && command != "w") {
        return false;
    }
    else {
        return true;
    }
}

// Check if the number list typed manually is correct of not. It
// will print out the smallest missing value.
bool check_number(std::vector<unsigned int> numbers){
    // First an array type bool that has 17 elements is created
    bool check_array[17] = {false};
    // Every element whose index showed up in the input vector will be true
    for (unsigned int i = 0 ; i < numbers.size() ; i++) {
        if ( numbers[i] >=1 && numbers[i] <= 16) {
            check_array[numbers[i]] = true;
        }
    }
    // The index of the first element which is false is missing
    for (unsigned int i = 1; i < 17; i++) {
        if (not check_array[i]) {
            std::cout << "Number " << i << " is missing" << std::endl;
            return false;
        }
     }
    return true;
}
int main()
{
    Board grid;
    std::string command;
    std::cout << "Random initialization (y/n): " ;

    // Read the command and then check it with check function mentioned above
    getline(std::cin, command);
    check_initial_command(command);
    // User chose to use the random board
    if (command =="y" || command == "Y") {
        std::cout << "Give a seed value or an empty line: " ;
        getline(std::cin, command);
        // If user did not typed in the seed value, seed value will be the time
        // else, the seed will be used to generate the random grid.
        if (command == "") {
            grid.initialize_random_board((int) time(0));
        }
        else {
            grid.initialize_random_board(stoi(command));
        }
    }
    // User chose to type the grid manually
    if (command == "n" || command == "N") {
        // Create an one-dimentional vector to store the input
        std::vector<unsigned int> numbers ={};
        // Here I used a temporary variable to insert input values in to
        // the vector created.
        unsigned int temp;
        std::cout << "Enter the numbers 1-16 in a "
                     "desired order (16 means empty):" << std::endl;
        for (unsigned int i = 0; i < 16; ++i){
            std::cin >>temp;
            numbers.push_back(temp);
        }
        std::string newline;
        getline(std::cin, newline);
        // Now check the input, if it is wrong, program terminates with return value EXIT_FAILURE
        if(not check_number(numbers)) {
            return EXIT_FAILURE;
        }
        // else, initialize the grid manually
        else {
            grid.initialize_manual_board(numbers);
        }
    }
    // After initializing the grid, check if it is solvable. If it isn't, the program terminates.
    if (not grid.is_solvable()) {
        std::cout <<"Game is not solvable. What a pity." << std::endl;
        return EXIT_SUCCESS;
    }
    // Else, print out the notification and then print the grid out
    std::cout << "Game is solvable: Go ahead!" << std::endl;
    // The game will continue until player type in quit command "q" or win
    // Every time the command is typed, the grid will be drawn again.
    while (true) {
        std::string row;
        grid.print();
        // Print out the notification when the player has won.
        if (grid.has_won()) {
            std::cout << "You won!" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << "Dir (command, number): ";
        getline(std::cin, row);
        // The program terminates when quit command is typed. 
        if (row == "q"){
            return EXIT_SUCCESS;
        }
        else {
            // If the player typed in other command, including direction and 
            // position . ALso check if the command are in the right syntax.
            unsigned int separator_index = row.find(' ');
            command = row.substr(0,separator_index);
            unsigned int num = stoi(row.substr(separator_index+1));
            if (check_moving_command(command) && num >=1 && num <=16) {
                grid.move_in_direction(command, num);
            }
            else if (not check_moving_command(command)) {
                std::cout << "Unknown command: " << command << std::endl;
            }
            else if (num <1 || num >16) {
                std::cout << "Invalid number: " << num << std::endl;
            }
        }
   }
    return EXIT_SUCCESS;
}
