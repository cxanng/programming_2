#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string key, original = "abcdefghijklmnopqrstuvwxyz", encrypt, result;
    cout << "Enter the encryption key: ";
    cin >> key;

    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
    }
    else {
        int i =0;
        for (i; i <26 ; i++) {
            char ch = key.at(i);
            if (isupper(ch)) {
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return 0;
            }
        }
        for (i=0; i <26; i++) {
            if (key.find(original.at(i)) == string::npos) {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;

            }
            else {
                cout << "Enter the text to be encrypted: ";
                cin >> encrypt;
                for (i=0 ;i < encrypt.length(); i++) {
                    result += key.at(original.find(encrypt.at(i)));
                }
            }
        }
        cout << "Encrypted text: " << result << endl;
    }
    return 0;
}
