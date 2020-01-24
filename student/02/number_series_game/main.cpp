#include <iostream>

using namespace std;
int main()
{
    cout << "How many numbers would you like to have? ";
    int count = 1, num;
    cin >> num;
    while (count <= num) {
        if (count % 3 == 0 && count % 7 !=0) {
                cout << "zip";
                }
                else if (count % 3 != 0 &&count % 7 ==0) {
                        cout << "boing";
                }
                else if (count % 3 == 0 && count % 7 ==0) {
                        cout << "zip boing";
                }
                else {
                        cout << count;
                }
                count++;

        }
        return 0;

}
