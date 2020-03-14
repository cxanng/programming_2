#include <iostream>
#include <string>

bool check(int i) {
    if(i ==1) {
        std::cout << "Error: Too few operands" << std::endl;
        return false;
    }
    else if(i == 0) {
        std::cout << "Error: Expression must start with a number" << std::endl;
        return false;
    }
    else {
        return true;
    }
}
int main()
{
    char ch = ' ';
    std::cout << "Input an expression in reverse Polish notation (end with #): " << std::endl;
    std::cout << "EXPR> ";
    int number_list[80];
    int i = 0;
    while (ch != '#') {
        std::cin >> ch;
        if (ch == ' ' || ch == '#' ) {
            continue;
        }

        if(ch >= '0' && ch <= '9') {
            number_list[i] = ch-'0';
            i++;
        }

        else if (ch == '+') {
            if (! check(i)) {
                return EXIT_FAILURE;
            }
            number_list[i-2] = number_list[i-1] + number_list[i-2];
            i--;
        }

        else if (ch == '-') {
            if (! check(i)) {
                return EXIT_FAILURE;
            }
            number_list[i-2] = number_list[i-2] - number_list[i-1];
            i--;
        }

        else if (ch == '*') {
            if (! check(i)) {
                return EXIT_FAILURE;
            }
            number_list[i-2] = number_list[i-2] * number_list[i-1];
            i--;
        }

        else if (ch == '/') {
            if (! check(i)) {
                return EXIT_FAILURE;
            }
            if (number_list[i-1] == 0) {
                std::cout << "Error: Division by zero" << std::endl;
                return EXIT_FAILURE;
            }
            else {
                number_list[i-2] = number_list[i-2] / number_list[i-1];
                i--;
            }
        }

        else {
            std::cout << "Error: Unknown character" << std::endl;
            return EXIT_FAILURE;
        }
    }
    if (i >= 2) {
        std::cout << "Error: Too few operators" << std::endl;
        return EXIT_FAILURE;
    }
    else {
        std::cout <<  " Correct: " << number_list[0] << " is the result" << std::endl;
        return EXIT_SUCCESS;
    }
}
