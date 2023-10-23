#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Player
{
    std::string name;
    int numGuesses;
};

void getPlayerName(std::string &name)
{
    std::cout << "Please enter your name to start: ";
    std::cin >> name;
}

void updateLeaderboard(std::vector<Player> &leaders, Player player)
{
    std::cout << "You made " << player.numGuesses << " guess" << (player.numGuesses == 1 ? "" : "es") << "." << std::endl;

    for (size_t i = 0; i < leaders.size(); i++)
    {
        if (player.numGuesses < leaders[i].numGuesses)
        {
            leaders.insert(leaders.begin() + i, player);
            break;
        }
    }

    std::cout << "Here are the current leaders:" << std::endl;
    for (const Player &leader : leaders)
    {
        std::cout << leader.name << " made " << leader.numGuesses << " guess" << (leader.numGuesses == 1 ? "" : "es") << std::endl;
    }
}

void saveLeadersToFile(const std::vector<Player> &leaders, const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    for (const Player &leader : leaders)
    {
        file << leader.name << " " << leader.numGuesses << "\n";
    }
}

void loadLeadersFromFile(std::vector<Player> &leaders, const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file" << std::endl;
        return;
    }

    Player leader;
    while (file >> leader.name >> leader.numGuesses)
    {
        leaders.push_back(leader);
    }
}

int getGuess()
{
    int guess;
    std::cout << "Guess a value between 10 and 100: ";
    std::cin >> guess;
    return guess;
}

int playGuessingGame()
{
    int root = std::sqrt(std::rand() % 91 + 10);
    std::cout << root << " is the square root of what number? ";
    int guess = getGuess();
    int answer = root * root;
    bool solved = false;
    Player player;
    player.numGuesses = 0;

    while (!solved)
    {
        player.numGuesses++;

        if (guess == answer)
        {
            std::cout << "You got it, baby!" << std::endl;
            solved = true;
            break;
        }
        else if (guess < answer)
        {
            std::cout << "Too low, guess again: ";
            guess = getGuess();
        }
        else
        {
            std::cout << "Too high, guess again: ";
            guess = getGuess();
        }
    }

    return player.numGuesses;
}

int main()
{
    std::srand(static_cast<unsigned int>(0));
    std::cout << "Welcome! Press 'q' to quit or any other key to continue:" << std::endl;
    char input;
    int numLeaders = 5;
    std::vector<Player> leaders;

    loadLeadersFromFile(leaders, "leaders.txt");

    while (true)
    {
        std::cin >> input;

        if (input == 'q' || input == 'Q')
        {
            std::cout << "Bye Bye!" << std::endl;

            saveLeadersToFile(leaders, "leaders.txt");
            break;
        }
        else
        {

            std::string playerName;
            getPlayerName(playerName);

            int numGuesses = playGuessingGame();

            Player currentPlayer;
            currentPlayer.name = playerName;
            currentPlayer.numGuesses = numGuesses;
            updateLeaderboard(leaders, currentPlayer);
        }
    }

    return 0;
}
