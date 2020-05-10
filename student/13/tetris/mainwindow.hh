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

private:
    Ui::MainWindow *ui;

    QGraphicsScene* scene_;




    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods

    const int EMPTY = -1;

    // A grid that contains position of blocks
    std::vector<std::vector<int>> game_grid_;

};

#endif // MAINWINDOW_HH
