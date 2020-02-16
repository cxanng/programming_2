#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <array>

int main()
{
    std::string infile_name;
    std::cout << "Input file: "; std::getline(std::cin, infile_name);
    std::ifstream file_object(infile_name);
    if (! file_object)
    {
        std::cout << "Error! The file " << infile_name << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    std::map< std::string , std::vector<int>> word_list;
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(file_object, line)) {
        std::string word;
        for (auto ch: line){
            if (ch != ' ') {
                word += ch;
            }
            else {
                word_list[word] = {};
                word = "";
            }
        }
        word_list[word] = {};
        lines.push_back(line);
    }
    int index = 1;
    for(auto line : lines) {
        for (auto word: word_list) {
            std::string::size_type temp = line.find(" " + word.first + " ") ;
            if (temp != std::string::npos) {
                word_list[word.first].push_back(index);
            }
        }
        ++index;
    }

    for (auto word : word_list) {
        std:: cout << word.first << " " << word_list[word.first].size() << ": " ;
        if (word_list[word.first].size() == 1) {
            std::cout << word_list[word.first][0] << std::endl;
        }
        else {
            for (unsigned int i = 0 ; i < word_list[word.first].size()-1; i++) {
                std::cout << word_list[word.first][i] << ", ";
            }
            std::cout << word_list[word.first].back() << std::endl;
        }
    }
    return 0;
}
