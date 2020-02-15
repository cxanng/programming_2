#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }
        std::vector<char> letters;
        if (word.size() > 3)
        {
            for (unsigned int i = 0 ; i < word.size() ; ++i)
            {
                letters.push_back(word.at(i));
            }
            std::vector<char>::iterator second_letter = letters.begin() +1;
            std::vector<char>::iterator second_last_lettor = letters.end() -1;
            shuffle(second_letter, second_last_lettor, generator);
            word = "";
            for (auto ch: letters)
            {
                word += ch;
            }
        }

	
        std::cout << word << std::endl;
    }
}
