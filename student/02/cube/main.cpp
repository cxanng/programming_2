#include <iostream>

using namespace std;

int main() {
    int x, cube;
    cout << "Enter a number: " ;
    cin >> x;
    cube = x * x * x;
    if (x >= 0 && x<= 1291 ) {
        cout << "The cube of " << x << " is " << x*x*x << "." <<endl;
    }
    else {
        cout << "Error! The cube of " << x << " is not " << cube << endl;
    }
    return 0;
}
