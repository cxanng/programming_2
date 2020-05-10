/* Class: Tetromino
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Class that represent a tetromino piece.
 * This includes some basic function for a tetromino piece such as
 * initializing, moving horizontally, dropping or rotating, ...
 *
 * Student's information:
 *
 * Name: The Anh Nguyen
 * Student number: 292126
 * User ID: cxanng
 * Email: anh.t.nguyen@tuni.fi
 *
 * */

#ifndef TETROMINO_HH
#define TETROMINO_HH

#include <map>
#include <string>
#include <vector>
#include <utility>

// Number of blocks in one tetromino piece
const int NUMBER_OF_BLOCKS = 4;

class Tetromino
{
public:

    Tetromino();

    // Sets initial coordinates to each block of the tetromino
    void initialize_tetromino(int tetromino_kind, int x, int y);

    // Changes the coordinates of each block of the tetromino as the
    // piece is moving
    void dropping();
    void rotating();
    void moving_horizontally(bool is_left);

    // Returns the type of the tetromino piece
    int get_type();

    // Initializes the piece setting exactly as an existing piece
    void set_tetromino(Tetromino new_tetromino);

    // Returns coordinates of a block of the tetromino piece
    std::pair<int, int> get_coordinate(int part_number);


private:

    // Type of the tetromino
    int kind_;

    // Initial position of the central piece
    int x_;
    int y_;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // List that includes coordinate of 4 blocks of the tetromino
    std::map<int, std::pair<int, int>> list_;

};

#endif // TETROMINO_HH
