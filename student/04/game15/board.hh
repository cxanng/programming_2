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
    
    // More methods
    void initialize_random_board(int seed);
    void initialize_manual_board(std::vector<unsigned int> numbers);
    std::vector<int> find_location(unsigned int number);
    void move_in_direction(std::string command, int position);
    void swap_two_pieces(std::vector<int> location1,std::vector<int> location2);
    bool has_won();
    bool is_solvable();
private:
    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(std::vector<unsigned int>& numbers, int seed);

    // Game grid for the 15 puzzle
    std::vector<std::vector<unsigned int>> grid_;

    // More attributes/methods
};

#endif // BOARD_HH
