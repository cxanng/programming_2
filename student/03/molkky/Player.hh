#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>
using namespace std;
class Player
{
public:
    Player( string name);
    string get_name() const;
    void add_points(int number);
    int get_points();
    bool has_won();
private:
    int points_;
    string name_;
};

#endif // PLAYER_H
