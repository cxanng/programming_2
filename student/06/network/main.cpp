#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
void print( std::map<std::string, std::vector<std::string>> list, std::string id, unsigned int count = 1) {
    std::cout << id << std::endl;
    if (list[id].size() > 0) {
        for ( auto name : list[id] ) {
            for (unsigned int i = 0; i < count; i++){
                std::cout << "..";
            }
            print(list, name, count + 1);
        }
    }
}

unsigned int count(std::map<std::string, std::vector<std::string>> list, std::string id) {
    if (list[id].size() <1 ) {
        return 0;
    }
    unsigned int result = list[id].size();
    for (auto name : list[id]) {
        result += count(list, name);
    }
    return result;
}

unsigned int depth(std::map<std::string, std::vector<std::string>> list, std::string id) {
    if (list.size() <1 ) {
        return 1;
    }
    unsigned int result = 1;
    for (auto name : list[id] ) {
        if (depth(list, name) >= result) {
            result = depth(list, name) + 1;
        }
    }
    return result;
}

int main()
{
    // TODO: Implement the datastructure here
    std::map <std::string, std::vector <std::string>> list;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            list[id1].push_back(id2);

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            print(list, id);


        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << count(list, id) << std::endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            std::cout << depth(list, id) << std::endl;

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
