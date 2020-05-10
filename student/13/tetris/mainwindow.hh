#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "tetromino.hh"
#include <QMainWindow>
#include <QGraphicsScene>
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

private slots:
    void initialize_game_grid();
    void render_current();
    void create_new_piece(int next_piece_type);
    void dropping_current();
    void redraw_current_piece(int type);
    bool game_over();
    void delete_completed_row();
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
