#include <iostream>

using namespace std;
int main()
{
    int count = 1, num;
        cout << "How many numbers would you like to have? ";

    cin >> num;
    while (count <= num) {
        if (count % 3 == 0 && count % 7 !=0) {
                cout << "zip" << endl;
                }
                else if (count % 3 != 0 && count % 7 ==0) {
                        cout << "boing" << endl;
                }
                else if (count % 3 == 0 && count % 7 ==0) {
                        cout << "zip boing" << endl;
                }
                else {
                        cout << count << endl;
                }
                count++;

        }
        return 0;

}
