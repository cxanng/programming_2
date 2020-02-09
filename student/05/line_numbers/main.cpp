#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string infile_name, outfile_name;
    std::cout << "Input file: ";
    std::cin >> infile_name;
    std::cout << "Out file: ";
    std::cin >> outfile_name;
    std::ifstream instream;
    instream.open(infile_name);
    if (instream.fail()) {
        std::ofstream outstream;
        outstream.open(outfile_name);
        unsigned int i = 1;
        while (not instream.eof()) {
            std::string line = "";
            getline(instream, line);
            outstream << i << " " << line;
            i++;
        }
        instream.close();
        outstream.close();
    }
    else {
        std::cout << "Error! The file " << infile_name << " can not be opened." << std::endl;
    }
    return 0;
}
