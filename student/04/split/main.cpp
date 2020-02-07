#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

std::vector < std::string > split(std::string str, char separator, bool empty = false) {
    std::vector < std::string > list;
    std::string element = "";
    std::string copied_str = str;
    int n = copied_str.length();
    for (int i=0; i < n ; i++) {
        if (copied_str.at(i) != separator) {
            element += copied_str.at(i);
        }
        else {
            if (empty) {
                if (element != "") {
                    list.push_back(element);
                }
            }
            else {
                list.push_back(element);
            }
            element ="";
        }
    }
    if (empty) {
        if (element != "") {
            list.push_back(element);
        }
    }


    return list;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
    return EXIT_SUCCESS;
}
