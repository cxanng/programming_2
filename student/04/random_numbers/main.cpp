#include <iostream>
#include <random>
#include <string>
#include <ctime>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    string command_1, command_2;
    cout << "Enter a seed value or an empty line: ";
    getline(cin, command_1);
    if (command_1 == "" ) {
        default_random_engine randomGenerator(time(0));
        uniform_int_distribution<int> randomNum(lower, upper);

        cout << "Your drawn random number is " << randomNum(randomGenerator) << endl;
        cout << "Press enter to continue or q to quit: " ;
        getline(cin, command_2);
        while (command_2 !="q") {
            cout << "Your drawn random number is " << randomNum(randomGenerator) << endl;
            cout << "Press enter to continue or q to quit: " ;
            getline(cin, command_2);
        }



    }
    else {
        default_random_engine randomGenerator(stoi(command_1));
        uniform_int_distribution<int> randomNum(lower, upper);

        cout << "Your drawn random number is " << randomNum(randomGenerator) << endl ;
        cout << "Press enter to continue or q to quit: " ;
        getline(cin, command_2);
        while (command_2 !="q") {
            cout << "Your drawn random number is " << randomNum(randomGenerator) << endl;
            cout << "Press enter to continue or q to quit: " ;
            getline(cin, command_2);
        }
    }
}
int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    // Reading the line feed, which was left unread by >> operator above.
    // This is necessary since the seed value will be read by getline
    // in the function produce_random_numbers.
    string line_feed = "";
    getline(cin, line_feed);

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound" << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
