#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QList>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QWidget>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    current_piece_(),
    next_piece_(),
    current_score(0),
    is_started_(false)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);
    display_next = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.
    timer_ = new QTimer();
    connect(timer_, &QTimer::timeout, this, &MainWindow::dropping_current);
    connect(ui->startPushButton, &QPushButton::clicked, this, &MainWindow::game_start);
    connect(ui->pausePushButton, &QPushButton::clicked, this, &MainWindow::pause);
    connect(ui->resumePushButton, &QPushButton::clicked, this, &MainWindow::resume);
    connect(ui->restartPushButton, &QPushButton::clicked, this, &MainWindow::restart);
    connect(ui->quitPushButton, &QPushButton::clicked, this, &MainWindow::quit);

    ui->displayNextGraphicsView->setScene(display_next);
    MainWindow::initialize_game_grid();
    next_piece_.initialize_tetromino(int(distr(randomEng)), COLUMNS/2 -1, 0);
    MainWindow::create_new_piece(int(distr(randomEng)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize_game_grid() {
    game_grid_ = {};

    for(int i = 0; i < ROWS; i++) {
        std::vector<int> row = {};
        for (int j = 0; j < COLUMNS; j++) {
            row.push_back(EMPTY);
        }
        game_grid_.push_back(row);
    }
}

void MainWindow::render_current() {
    scene_->clear();
    display_next->clear();

    QPen blackPen(Qt::black);
    blackPen.setWidth(1);

    std::map<int, QBrush> color;
    color[HORIZONTAL] = QBrush(Qt::cyan);
    color[LEFT_CORNER] = QBrush(Qt::blue);
    color[RIGHT_CORNER] = QBrush(Qt::gray);
    color[SQUARE] = QBrush(Qt::yellow);
    color[STEP_UP_RIGHT] = QBrush(Qt::green);
    color[PYRAMID] = QBrush(Qt::magenta);
    color[STEP_UP_LEFT] = QBrush(Qt::red);
    color[EMPTY] = QBrush(Qt::white);

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (game_grid_[i][j] != EMPTY) {
                int x = SQUARE_SIDE * j;
                int y = SQUARE_SIDE * i;
                scene_->addRect(x, y, SQUARE_SIDE, SQUARE_SIDE,
                                        blackPen, color[game_grid_[i][j]]);
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        int x = next_piece_.get_coordinate(i).first - 3;
        int y = next_piece_.get_coordinate(i).second + 1;
        display_next->addRect(x * SQUARE_SIDE, y * SQUARE_SIDE,
                                      SQUARE_SIDE, SQUARE_SIDE, blackPen,
                                      color[next_piece_.get_type()]);

    }
}

void MainWindow::create_new_piece(int next_piece_type) {
    current_piece_.set_tetromino(next_piece_);
    next_piece_.initialize_tetromino(next_piece_type, 5, 0);
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        game_grid_[current_piece_.get_coordinate(i).second]
                  [current_piece_.get_coordinate(i).first] = current_piece_.get_type();
    }
}

void MainWindow::dropping_current() {
    bool able_to_move = true;
    MainWindow::redraw_current_piece(EMPTY);

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        if (current_piece_.get_coordinate(i).second == ROWS - 1
                || game_grid_[current_piece_.get_coordinate(i).second + 1]
                [current_piece_.get_coordinate(i).first] != EMPTY) {
            able_to_move = false;
        }
    }

    if (able_to_move) {
        current_piece_.dropping();
        MainWindow::redraw_current_piece(current_piece_.get_type());
    }
    else {
        // renew coordinates of the tetromino
        MainWindow::redraw_current_piece(current_piece_.get_type());
        MainWindow::delete_completed_row();
        if (!MainWindow::game_over()) {
            MainWindow::create_new_piece(int(distr(randomEng)));
        }
        else {
            timer_->stop();
            is_started_ = false;
            ui->gameOverStatus->setText(" GAME OVER !");
        }
    }

    MainWindow::render_current();
}

void MainWindow::redraw_current_piece(int type) {
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        game_grid_[current_piece_.get_coordinate(i).second]
                  [current_piece_.get_coordinate(i).first] = type;
    }
}

bool MainWindow::game_over() {
    bool result = false;
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        if (game_grid_[next_piece_.get_coordinate(i).second]
                [next_piece_.get_coordinate(i).first] != EMPTY) {
            result = true;
        }
    }
    return result;
}

void MainWindow::delete_completed_row() {
    std::vector<int> completed_rows = {};
    for (int i = 0; i < ROWS; i ++) {
        bool complete = true;
        for (int j = 0; j < COLUMNS; j++) {
            if (game_grid_[i][j] == EMPTY) {
                complete = false;
            }
        }
        if (complete) {
            completed_rows.push_back(i);
            current_score += 10;
            if (current_score < 300) {
                timer_->start(500 - current_score);
            }
        }
    }
    for (auto row : completed_rows) {
        for (int i = 0; i < row; i++) {
            game_grid_[row-i] = game_grid_[row-i-1];
        }
        for (int j = 0; j < COLUMNS; j++) {
            game_grid_[0].push_back(EMPTY);
        }
    }
    ui->lcdNumberScore->display(current_score);
}

void MainWindow::quick_dropping() {
    bool able_to_move = true;
    MainWindow::redraw_current_piece(EMPTY);

    while (true) {
        for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
            if (current_piece_.get_coordinate(i).second == ROWS - 1
                    || game_grid_[current_piece_.get_coordinate(i).second + 1]
                    [current_piece_.get_coordinate(i).first] != EMPTY) {
                able_to_move = false;
            }
        }
        if (able_to_move) {
            current_piece_.dropping();
        }
        else {
            MainWindow::redraw_current_piece(current_piece_.get_type());
            break;
        }
    }
}

void MainWindow::game_start() {
    MainWindow::initialize_game_grid();
    if (!is_started_) {
        int time_interval = 500;
        timer_->setSingleShot(false);
        timer_->start(time_interval);
        is_started_ = true;
        ui->startPushButton->setDisabled(true);
        ui->resumePushButton->setDisabled(true);
    }
}

void MainWindow::pause() {
    timer_->stop();
    is_started_ = false;
    ui->resumePushButton->setEnabled(true);
    ui->pausePushButton->setDisabled(true);
}

void MainWindow::resume() {
    timer_->start();
    ui->resumePushButton->setDisabled(true);
    ui->pausePushButton->setEnabled(true);
}

void MainWindow::restart() {
    if (!is_started_) {
        scene_->clear();
        MainWindow::create_new_piece(int(distr(randomEng)));
        MainWindow::game_start();
        ui->pausePushButton->setEnabled(true);
    }
}

void MainWindow::quit() {
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if (!is_started_) {
        return;
    }

    bool able_to_move = true;

    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        game_grid_[current_piece_.get_coordinate(i).second]
                  [current_piece_.get_coordinate(i).first] = EMPTY;
    }

    switch (event->key()) {
       case Qt::Key_A: {
           for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
               if (current_piece_.get_coordinate(i).first == 0
                       || game_grid_[current_piece_.get_coordinate(i).second]
                       [current_piece_.get_coordinate(i).first - 1] != EMPTY) {
                   able_to_move = false;
               }
           }
           if (able_to_move) {
               current_piece_.moving_horizontally(true);
               MainWindow::redraw_current_piece(current_piece_.get_type());
           }
           break;
       }
       case Qt::Key_D: {
           for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
               if (current_piece_.get_coordinate(i).first == COLUMNS -1
                       || game_grid_[current_piece_.get_coordinate(i).second]
                       [current_piece_.get_coordinate(i).first + 1] != EMPTY) {
                   able_to_move = false;
               }
           }
           if (able_to_move) {
               current_piece_.moving_horizontally(false);
               MainWindow::redraw_current_piece(current_piece_.get_type());
           }
           break;
        }

        case Qt::Key_S : {
            MainWindow::quick_dropping();
            break;
        }

        case Qt::Key_R: {
            Tetromino test_block;
            test_block.set_tetromino(current_piece_);
            bool able_to_rotate = true;
            MainWindow::redraw_current_piece(EMPTY);
            test_block.rotating();

            for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
                if (test_block.get_coordinate(i).second <0
                    ||test_block.get_coordinate(i).second > ROWS -1
                    ||test_block.get_coordinate(i).first < 0
                    || test_block.get_coordinate(i).first > COLUMNS -1
                    || game_grid_[test_block.get_coordinate(i).second]
                        [test_block.get_coordinate(i).first] != EMPTY) {
                    able_to_rotate = false;
                }
            }
            if (able_to_rotate) {
                current_piece_.rotating();
                MainWindow::redraw_current_piece(current_piece_.get_type());
                }
            break;
        }
    MainWindow::render_current();

    }
}
