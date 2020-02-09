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
std::string check_initial_command(std::string& command) {
    // Check the first command to choose random initialization or not
    while (command !="y" && command !="Y" && command != "n" && command != "N" ){
        std::cout << "Unknown choice: " << command << std::endl;
        std::cout << "Random initialization (y/n): " ;
        getline(std::cin, command);
    }
    return command;
}

bool check_moving_command(std::string command) {
    if (command != "a" && command != "s" && command != "d" && command != "w" && command != "q") {
        return false;
    }
    else {
        return true;
    }
}

bool check_number(std::vector<unsigned int> numbers){
    bool check_array[17] = {false};
    for (unsigned int i = 0 ; i < numbers.size() ; i++) {
        if ( numbers[i] >=1 && numbers[i] <= 16) {
            check_array[numbers[i]] = true;
        }
    }
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
    // More functionality
    Board grid;
    std::string command;
    std::cout << "Random initialization (y/n): " ;
    getline(std::cin, command);
    check_initial_command(command);

    if (command =="y" || command == "Y") {
        std::cout << "Give a seed value or an empty line: " ;
        getline(std::cin, command);
        if (command == "") {
            grid.initialize_random_board((int) time(0));
        }
        else {
            grid.initialize_random_board(stoi(command));
        }
    }



    if (command == "n" || command == "N") {
        std::vector<unsigned int> numbers ={};
        unsigned int temp;
        std::cout << "Enter the numbers 1-16 in a "
                     "desired order (16 means empty):" << std::endl;
        for (unsigned int i = 0; i < 16; i++){
            std::cin >>temp;
            numbers.push_back(temp);
        }
        std::string newline;
        getline(std::cin, newline);
        // If input is wrong, stop the program with return value EXIT_FAILURE.
        if(not check_number(numbers)) {
            return EXIT_FAILURE;
        }
        else {
            grid.initialize_manual_board(numbers);
        }
    }

    while (true) {
        std::string row;
        if (not grid.is_solvable()) {
            std::cout <<"Game is not solvable. What a pity." << std::endl;
            return EXIT_SUCCESS;
        }
        grid.print();
        std::cout << "Game is solvable: Go ahead!" << std::endl;
        if (grid.has_won()) {
            std::cout << "You won!" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << "Dir (command, number): ";
        getline(std::cin, row);
        command = row.front();

        if (command == "q"){
            return EXIT_SUCCESS;
        }
        else {
            unsigned int num = stoi(row.substr(2));
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
