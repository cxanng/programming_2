#include "tetromino.hh"
#include <utility>
#include <QDebug>

Tetromino::Tetromino():
    kind_(0),
    x_(0),
    y_(0)
{

}

void Tetromino::initialize_tetromino(int tetromino_kind, int x, int y) {
    kind_ = tetromino_kind;
    x_ = x;
    y_ = y;

    if (kind_ ==  HORIZONTAL) {
        list_[0] = {x_-1, y_};
        list_[1] = {x_, y_};
        list_[2] = {x_+1, y_};
        list_[3] = {x_+2, y_};
    }
    else if (kind_ == LEFT_CORNER) {
        list_[0] = {x_, y_};
        list_[1] = {x_, y_+1};
        list_[2] = {x_+1, y_+1};
        list_[3] = {x_+2, y_+1};
    }
    else if (kind_ == RIGHT_CORNER) {
        list_[0] = {x_, y_+1};
        list_[1] = {x_+2, y_+1};
        list_[2] = {x_+1, y_+1};
        list_[3] = {x_+2, y_};
    }
    else if (kind_ == SQUARE) {
        list_[0] = {x_, y_};
        list_[1] = {x_+1,y_};
        list_[2] = {x_, y_+1};
        list_[3] = {x_+1, y_+1};
    }
    else if (kind_ == STEP_UP_RIGHT) {
        list_[0] = {x_, y_};
        list_[1] = {x_+1,y_};
        list_[2] = {x_, y_+1};
        list_[3] = {x_-1, y_+1};
    }
    else if (kind_ == PYRAMID) {
        list_[0] = {x_, y_};
        list_[1] = {x_-1,y_+1};
        list_[2] = {x_, y_+1};
        list_[3] = {x_+1, y_+1};
    }
    else if (kind_ == STEP_UP_LEFT) {
        list_[0] = {x_, y_};
        list_[1] = {x_-1,y_};
        list_[2] = {x_, y_+1};
        list_[3] = {x_+1, y_+1};
    }
}

void Tetromino::dropping() {

    for (int i = 0; i < 4; i++) {
        list_[i].second += 1;
    }
}

void Tetromino::moving_horizontally(bool is_left) {
    for (int i = 0; i < 4; i++) {
        if (is_left) {
            list_[i].first -= 1;
        }
        else {
            list_[i].first += 1;
        }
    }
}

void Tetromino::rotating() {
    int x0 = list_[2].first;
    int y0 = list_[2].second;
    for (int i = 0; i < 4; i++) {
        list_[i] = {x0 + y0 - list_[i].second, list_[i].first -x0 +y0};
    }
}

int Tetromino::get_type()
{
    return kind_;
}

std::pair<int, int> Tetromino::get_coordinate(int part_number) {
    return list_[part_number];
}

void Tetromino::set_tetromino(Tetromino new_tetromino) {
    list_[0] = new_tetromino.get_coordinate(0);
    list_[1] = new_tetromino.get_coordinate(1);
    list_[2] = new_tetromino.get_coordinate(2);
    list_[3] = new_tetromino.get_coordinate(3);
    kind_ = new_tetromino.get_type();
}
