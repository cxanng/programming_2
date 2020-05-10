#include "mainwindow.hh"
#include "ui_mainwindow.h"


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
}

void MainWindow::create_new_piece(int next_piece_type) {
    current_piece_.set_tetromino(next_piece_);
    next_piece_.initialize_tetromino(next_piece_type, 5, 0);
    for (int i = 0; i < NUMBER_OF_BLOCKS; i++) {
        game_grid_[current_piece_.get_coordinate(i).second]
                  [current_piece_.get_coordinate(i).first] = current_piece_.get_type();
    }
}
