#include <iostream>

using namespace std;
double factorial(int number) {
    double result =1 ;
    if (number == 0) {
        result = 1;
    }
    else {
        for (int i = 1; i <= number; i++) {
            result = result * i;
        }
    }
    return result;
}
int main() {
    int total, require;
    double result;
    cout << "Enter the total number of lottery balls: " ;
    cin >> total;
    cout << "Enter the number of drawn balls: " ;
    cin >> require;
    if (total >=0 && require >=0 && total >= require) {
        result = factorial(total) /( factorial(total - require) * factorial (require));
        cout << "The probability of guessing all " << require << " balls correctly is 1/" << (long int)(result) << endl;
    }
    else if (total <0 || require <0) {
        cout << "The number of balls must be a positive number." << endl;
    }
    else if (total < require) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
    }
    return 0;
}
