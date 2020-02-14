#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::string infile_name, outfile_name;
    std::cout << "Input file: ";
    std::cin >> infile_name;
    std::cout << "Output file: ";
    std::cin >> outfile_name;
    std::ifstream instream(infile_name);
    if (! instream) {
        std::cout << "Error! The file " << infile_name << " can not be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else {
        std::ofstream outstream(outfile_name);
        unsigned int i = 0;
        std::string line = "";
        while (std::getline(instream, line)) {
            ++i;
            outstream << i << " " << line << "\n";
        }
    }
    return 0;
}
