#include <iostream>
using namespace std;
int mean(int number_of_components)
{
        int i = 1, sum = 0, x;
        if (number_of_components >=1) {
                while (i <= number_of_components) {
                        cout << "Input " << i << ". number: ";
                        cin >> x;
                        sum += x;
                        i++;
                }
                cout << "Mean value of the given numbers is "<< (sum/number_of_components);
                return 0;

        }
        else {
                cout << "Cannot count mean value from 0 numbers";
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
