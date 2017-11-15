#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// declarations
void PrintIntro();
void PlayGame();
FText GetGuess();
void PrintGuess(FBullCowCount Guess);
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
    // intro
    std::cout << "Welcome to Bulls and Cows, a fun word game\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
    std::cout << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
}

void PlayGame()
{

    // get max tries
	BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop through turns.
    for (int32 count = 1; count <= MaxTries; count++)
    {
		FText Guess = GetGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        // get guess and print back
        PrintGuess(BullCowCount);
    }

	// TODO Summarize game
}

FText GetGuess()
{
    // current try
    int32 CurrentTry = BCGame.GetCurrentTry();

    // ask for guess
    FText Guess = "";
    std::cout << "Try " << CurrentTry << ". Enter your guess: ";

    // get guess
    std::getline(std::cin, Guess);

    return Guess;
}

void PrintGuess(FBullCowCount BullCowCount)
{
	std::cout << "Bulls = " << BullCowCount.Bulls;
	std::cout << " | Cows = " << BullCowCount.Cows;
	std::cout << "\n" << std::endl;
}

bool AskToPlayAgain()
{
    // ask to play again
    FText Response = "";
    std::cout << "Do you want to play again (y/n)? ";

    // get response
    std::getline(std::cin, Response);
    std::cout << std::endl;

    // return bool (y for true, anything else for false)
    return (Response[0] == 'y') || (Response[0] == 'Y');
}
