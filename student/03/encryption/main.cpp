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
        return EXIT_FAILURE;
    }
    else {
        int i;
        for (i=0; i <26 ; i++) {
            char ch = key.at(i);
            if (isupper(ch)) {
                cout << "Error! The encryption key must contain only lower case characters." << endl;
                return EXIT_FAILURE;
            }
        }
        for (i=0; i <26; i++) {
            if (key.find(original.at(i)) == string::npos) {
                cout << "Error! The encryption key must contain all alphabets a-z." << endl;
                return EXIT_FAILURE;
            }


            }
        }
    cout << "Enter the text to be encrypted: ";
    cin >> encrypt;
    int i;
    for (i =0;(unsigned) i< encrypt.length(); i++){
        result += key.at(original.find(encrypt.at(i)));
    }
    cout << "Encrypted text: " << result << endl;
    return 0;

    }

