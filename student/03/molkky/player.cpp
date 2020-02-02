#include "player.hh"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

Player::Player(string name): name_(name)
{

};

void Player::add_points(int number) {
        points_ += number;
        if (points_ > 50) {
            points_ = 25;
        }
    };
string Player::get_name() const {
        return name_;
    };
bool Player::has_won() {
        if (points_ == 50) {
            return true;
        }
        else {
            return false;
        }
    };
int Player::get_points(){
        return points_;
    };
