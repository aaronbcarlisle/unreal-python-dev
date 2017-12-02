#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

// declarations
void PrintIntro();
void PlayGame();
FText GetValidGuess();
void PrintTrySummary(FBullCowCount Guess);
bool AskToPlayAgain();
void PrintGameSummary();


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
	BCGame.Reset();

    // get max tries
    int32 MaxTries = BCGame.GetMaxTries();

    // loop through turns.
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
		FText Guess = GetValidGuess();

		// submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        // output guess from BullCowCount game
        PrintTrySummary(BullCowCount);
    }

	PrintGameSummary();
	return;
}

// loop until valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// current try
		int32 CurrentTry = BCGame.GetCurrentTry();

		// ask for guess
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries(); 
		std::cout << ". Enter your guess: ";

		// get guess
		std::getline(std::cin, Guess);

		// check guess validity
		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:
			// assume the guess is valid, break out of switch statement
			break;
		}
	} while (Status != EGuessStatus::OK);

	// return guess outside loop
	return Guess; 
}

void PrintTrySummary(FBullCowCount BullCowCount)
{
	std::cout << "Bulls = " << BullCowCount.Bulls;
	std::cout << " | Cows = " << BullCowCount.Cows;
	std::cout << "\n" << std::endl;
}

bool AskToPlayAgain()
{
    // ask to play again
    FText Response = "";
    std::cout << "Do you want to play again with the same hidden word (y/n)?\n";

    // get response
    std::getline(std::cin, Response);
    std::cout << std::endl;

    // return bool (y for true, anything else for false)
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "YOU WON - GOOD JOB!\n";
	}
	else
	{
		std::cout << "YOU LOSE - BETTER LUCK NEXT TIME!\n";
	}
	return;
}
