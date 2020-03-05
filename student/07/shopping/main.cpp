/*      Description:

// This program stores all the information about products that belong to
// different stores from an input file.
// It also provides some useful functions such as listing the chains, the
// stores belongs to those chains, the products and their prices or whether
// they are out of stock and find the stores selling cheapest product.

//  Students:
// 1. Name: The Anh Nguyen
//     Student number: 292126
//     UserID:cxanng
//     E-mail: anh.t.nguyen@tuni.fi

// 2. Name: Phuong Nhi Thuy Tran
//     Student number: 291937
//     UsedID:mpthtr
//     E-mail: thuyphuongnhi.tran@tuni.fi
* */




#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

struct Product {
    std::string product_name;
    double price;
};

void checked_list(std::vector<std::string>& list, std::string item){
    std::vector<std::string>::iterator iter = std::find(list.begin(), list.end(), item);
    if ( iter == list.end()) {
        list.push_back(item);
    }
}

void add_product(std::vector<Product>& list, Product new_item) {
    bool check = false;
    for (auto item : list) {
        if(item.product_name == new_item.product_name) {
            check = true;
            item.price = new_item.price;
        }
    }
    if (! check) {
        list.push_back(new_item);
    }
}

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

int main_loop() {
    while (true) {
       std::string line;
        std::string command;
        std::cout << "> " ;
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ');
        command = parts[0];

        if (command == "quit") {
            return EXIT_SUCCESS;
        }

        else if (command == "chains"){
            if (parts.size() != 1) {
                std::cout << "Error: error in command chains" << std::endl;
                continue;
            }
        }

        else if (command == "stores") {
            if (parts.size() != 2) {
                std::cout << "Error: error in command stores" << std::endl;
                continue;
            }
        }

        else if (command == "selection") {
            if (parts.size() != 3) {
                std::cout << "Error: error in command selection" << std::endl;
                continue;
            }
        }

        else if (command == "cheapest") {
            if (parts.size() != 2) {
                std::cout << "Error: error in command cheapest" << std::endl;
                continue;
            }
        }

        else if (command == "products") {
            if (parts.size() != 1) {
                std::cout << "Error: error in command products" << std::endl;
                continue;
            }
        }

        else {
            std::cout << "Error: unknown command: " << command <<std::endl;
        }
    }
}

int main()
{
    // Ask for input file name and store the information, also deal with reading errors
    std::cout << "Input file: ";
    std::string in_file = "";
    getline(std::cin, in_file);
    std::ifstream file_object(in_file);
    if (! file_object) {
        std::cout << "Error: the input file cannot be opened" <<std::endl;
        return EXIT_FAILURE;
    }
    std::map <std::string, std::map <std::string, std::vector<Product>>> chain_system;
    std::vector <std::string> product_list;
    std::string line;
    while (getline(file_object, line)) {
        if (split(line, ';').size() !=4 ) {
            std::cout << "Error: the input file has an erroneous line" <<std::endl;
            return EXIT_FAILURE;
        }
        std::vector <std::string> line_content = split(line, ';');
        Product item;

        if (line_content[3] == "out-of-stock") {
            item = {line_content[2], -1};
        }
        else {
            item = {line_content[2], stod(line_content[3])};
        } 
        add_product(chain_system[line_content[0]][line_content[1]],item);
        checked_list(product_list, line_content[2]);
    }
    return main_loop();
}
