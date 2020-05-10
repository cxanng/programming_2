#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "tetromino.hh"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>
#include <random>
#include <QTimer>
#include <QGraphicsRectItem>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    //  Receive the signal from the keyboard to control the tetrominos
    // This includes four commands:
    // A for moving left
    // D for moving right
    // S for immediate drop
    // R for rotating the tetromino clockwise
    void keyPressEvent(QKeyEvent* event);

private slots:
    // Controls the game play
    void restart();
    void pause();
    void resume();
    void quit();
    void game_start();

    // Initializes a gamce grid to save data from tetrominos
    void initialize_game_grid();

    // Draws the whole game grid
    void render_current();

    // Creates a new piece knowing the type of it
    void create_new_piece(int next_piece_type);

    // Controls the dropping of a tetromino
    void dropping_current();

    // Change the color of the tetromino, mostly used for detecting
    // if the tetromino is movable
    void redraw_current_piece(int type);

    // Determines if the game is over or not
    bool game_over();

    // Deletes a full rows
    void delete_completed_row();

    // Drops the tetromino as much as possible
    void quick_dropping();

private:
    Ui::MainWindow *ui;
    // Graphics scenes to display the game play and the next piece
    QGraphicsScene* scene_;
    QGraphicsScene* display_next;
    
    // Timer to 
    QTimer* timer_;
    Tetromino current_piece_;
    Tetromino next_piece_;
    int current_score;
    bool is_started_;

    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods

    const int EMPTY = -1;

    // A grid that contains position of blocks
    std::vector<std::vector<int>> game_grid_;

};

#endif // MAINWINDOW_HH
