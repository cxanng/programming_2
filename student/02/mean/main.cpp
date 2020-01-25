#include <iostream>
#include <iomanip>

using namespace std;

double mean(int number_of_components)
{
    int i = 1;
    double x;
    double sum = 0.0;
    while (i <= number_of_components) {
        cout << "Input " << i << ". number: ";
        cin >> x;
        sum += x;
        i++;
    }
    return (sum/number_of_components);
}

int main()
{
    int num;
    double result = 0.0;
    cout << "From how many integer numbers you want to count the mean value? ";
    cin >> num;
    if (num >= 1){
        result = mean(num);
        cout << "Mean value of the given numbers is " << std::setprecision(2) << result << endl;
    }
    else {
        cout << "Cannot count mean value from 0 numbers" << endl;
    }

    return EXIT_SUCCESS;
}
