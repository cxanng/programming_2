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

//std::string check_move_command(std::string &command) {
//    while(command != "a")
//}
bool check_number(std::vector<unsigned int> numbers){
    bool check_array[50] = {false};
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
        std::cout << "Enter the numbers 1-16 in a desired order (16 means empty):" << std::endl;
        for (unsigned int i = 0; i < 16; i++){
            std::cin >>temp;
            numbers.push_back(temp);
        }
        // If input is wrong, stop the program with return value EXIT_FAILURE.
        if(not check_number(numbers)) {
            return EXIT_FAILURE;
        }
        else {
            grid.initialize_manual_board(numbers);
        }

    }
    grid.print();

    return EXIT_SUCCESS;
}
