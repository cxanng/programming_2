/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
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

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <random>

const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

void Board::initialize_random_board(int seed)
{
    std::vector<unsigned int> numbers;
    for (unsigned int i =0; i < EMPTY ; i++) {
        numbers.push_back(i+1);
    }
    my_shuffle(numbers, seed);

    for (unsigned int i = 0; i < SIZE; i++) {
        std::vector <unsigned int> row;
        for (unsigned int j = 0; j < SIZE; j++) {
            row.push_back(numbers.at( SIZE * i +j));
        }
        this->grid_.push_back( row);

    }
}

void Board::initialize_manual_board(std::vector<unsigned int> numbers) {
    for (unsigned int i = 0; i < SIZE; i++) {
        std::vector <unsigned int> row;
        for (unsigned int j = 0; j < SIZE; j++) {
            row.push_back(numbers.at( SIZE * i +j));
        }
        this->grid_.push_back( row);

    }
}

std::vector<int> Board::find_location(unsigned int number) {
    std::vector<int> location = {};
    for (unsigned int i = 0; i < grid_.size(); i++) {
        for (unsigned int j = 0; j < SIZE; j++) {
            if (grid_.at(i).at(j) == number) {
                location.push_back(i);
                location.push_back(j);
            }
        }
    }
    return location;
}
void Board::move_in_direction(std::string command, int position) {
    std::vector <int> empty_location = find_location(16);
    std::vector <int> moving_location = find_location(position);
    if (command == "a") {
        // Check if the empty space is on the left of the moving piece
        if (empty_location[1] == moving_location[1] || empty_location[0] == moving_location[0] -1) {
        // Swap two value
            int temp = grid_.at(empty_location[0]).at(empty_location[1]);
            grid_.at(empty_location[0]).at(empty_location[1]) = grid_.at(moving_location[0]).at(moving_location[1]);
            grid_.at(moving_location[0]).at(moving_location[1]) = temp;
        }
        else {
            std::cout << "Impossible direction: " << command;
        }
    }

}



