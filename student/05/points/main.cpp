#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <fstream>
#include <utility>

bool compare_name(std::pair<std::string,int>  player1, std::pair<std::string,int>  player2) {
    return player1.first < player2.first;
}

int main()
{
    std::cout << "Input file: ";
    std::string infile_name;
    std::getline(std::cin, infile_name);
    std::ifstream file_object(infile_name);
    if (! file_object)
    {
        std::cout << "Error! The file " << infile_name << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::map <std::string , int> players_scores;
    std::map <std::string , int>::iterator iter;
    std::string line;

    while (getline(file_object, line))
    {
        int pos = line.find(":");
        std::string name = line.substr(0, pos);
        int score = std::stoi(line.substr(pos +1, line.size() - pos - 1));
        players_scores[name] += score;
    }
//    std::sort(players_scores.begin() , players_scores.end(), compare_name);
    std::cout << "Final scores:" << std::endl;
    for( auto player: players_scores )
    {
        std::cout << player.first << ": " << player.second << std::endl;
    }
    return EXIT_SUCCESS;
}
