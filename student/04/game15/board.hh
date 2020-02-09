/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author ( Fill with your own info )
 * Name: Nguyen The Anh
 * Student number: 292126
 * UserID: cxanng
 * E-Mail: anh.t.nguyen@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <string>

const int SIZE = 4;

class Board
{
public:
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way

    // Prints the game grid
    void print();
    
    // This function initializes a random grid
    void initialize_random_board(int seed);

    // This function takes an one-dimentional vector as the parameter
    // and initializes the two-dimentional board base on it
    void initialize_manual_board(std::vector<unsigned int> numbers);

    // This function is used to find the coodinates (row and column)
    // of the element.
    std::vector<int> find_location(unsigned int number);

    // This funtion handles the moving steps.
    void move_in_direction(std::string command, int position);

    // Check if player has won or not
    bool has_won();

    // Check if the initial situation is solvable or not.
    bool is_solvable();
private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);
    // This funtions swaps two pieces whose coodinates are mentioned.
    void swap_two_pieces(std::vector<int> location1,std::vector<int> location2);
    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;
};
#endif // BOARD_HH
