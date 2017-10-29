#include <iostream>
#include <string>
#include "FBullCowGame.h"

// declarations
void PrintIntro();
void PlayGame();
std::string GetGuess();
void PrintGuess(std::string Guess);
bool AskToPlayAgain();

// game instance
FBullCowGame BCGame;

int main()
{
    // play game
    bool bPlayAgain = false;
    do {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    }
    while (bPlayAgain);

    // exit application
    return 0;
}

void PrintIntro()
{
    // magic number for word length
    const int WORD_LENGTH = 8;

    // intro
    std::cout << "Welcome to Bulls and Cows, a fun word game\n";
    std::cout << "Can you guess the " << WORD_LENGTH;
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
}

void PlayGame()
{

    // get max tries
    int MaxTries = BCGame.GetMaxTries();

    // loop through turns.
    for (int count = 1; count <= MaxTries; count++)
    {
        // get guess and print back
        PrintGuess(GetGuess());
    }
}

std::string GetGuess()
{
    // current try
    int CurrentTry = BCGame.GetCurrentTry();

    // ask for guess
    std::string Guess = "";
    std::cout << "Try " << CurrentTry << ". Enter your guess: ";

    // get guess
    std::getline(std::cin, Guess);

    return Guess;
}

void PrintGuess(std::string Guess)
{
    // repeat the guess back
    std::cout << "Your guess was: " << Guess << std::endl;
    std::cout << std::endl;
}

bool AskToPlayAgain()
{
    // ask to play again
    std::string Response = "";
    std::cout << "Do you want to play again (y/n)? ";

    // get response
    std::getline(std::cin, Response);
    std::cout << std::endl;

    // return bool (y for true, anything else for false)
    return (Response[0] == 'y') || (Response[0] == 'Y');
}
