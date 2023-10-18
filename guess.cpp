#include <iostream>

using namespace std;

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    int secretNum = rand() % 101;
    int guess;
    int guessCount = 0;
    int guessLimit = 5;
    bool outOfGuesses = false;

    while (secretNum != guess && !outOfGuesses)
    {
        if (guessCount < guessLimit)
        {
            cout << "Enter guess: ";
            cin >> guess;
            guessCount++;

            if (guess < secretNum)
            {
                cout << "Too low!" << endl;
            }
            else if (guess > secretNum)
            {
                cout << "Too high!" << endl;
            }
        }
        else
        {
            outOfGuesses = true;
        }
    }

    if (outOfGuesses)
    {
        cout << "You lose! The secret number was " << secretNum << "." << endl;
    }
    else
    {
        cout << "You win! The secret number was " << secretNum << "." << endl;
    }

    return 0;
}
