#include <iostream>
using namespace std;
int mean(int number_of_components)
{
        int i = 1;
        float sum = 0, x, result;
        if (number_of_components >=1) {
                while (i <= number_of_components) {
                        cout << "Input " << i << ". number: ";
                        cin >> x;
                        sum += x;
                        i++;
                }
                return (sum/number_of_components);
                cout << "Mean value of the given numbers is "<< sum/number_of_components;

        }
        else {
                cout << "Cannot count mean value from 0 numbers";
                return 0;
        }
}

int main()
{
    int num;
        cout << "From how many integer numbers you want to count the mean value? ";
    cin >> num;
    mean(num);
    return 0;
}
