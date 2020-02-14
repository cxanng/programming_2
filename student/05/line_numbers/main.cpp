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
//    instream.open(infile_name);
    std::ofstream outstream(outfile_name);
//    outstream.open(outfile_name);
    if (not instream) {
        std::cout << "Error! The file " << infile_name << " can not be opened." << std::endl;
    }
    else {
        unsigned int i = 1;
        while (not instream.eof()) {
            std::string line = "";
            std::getline(instream, line);
            if (line != "") {
                outstream << i << " " << line << "\n";
                i++;
            }
        }
//        instream.close();
//        outstream.close();
    }
    return 0;
}
