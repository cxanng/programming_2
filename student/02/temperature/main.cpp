#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int temp;

    cin >> temp;
    cout << temp << " degrees Celsius is " << 1.8* temp +32 << " degrees Fahrenheit" <<endl;
    cout << temp << " degrees Fahrenheit is " << (temp - 32)/1.8 << " degree Celsius" << endl;
    return 0;
}
