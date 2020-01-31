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
    result = factorial(total) /( factorial(total - require) * factorial (require));
    cout << "The probability of guessing all " << require << " balls correctly is 1/" << (long int)(result) << endl;

    return 0;
}
