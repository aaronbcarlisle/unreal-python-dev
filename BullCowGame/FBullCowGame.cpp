#include <iostream>
#include "FBullCowGame.h"

// constructor
FBullCowGame::FBullCowGame() { Reset(); }

// getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return true; }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyMaxTries = MAX_TRIES;

	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	return;
}


bool FBullCowGame::CheckGuessValidity(FString)
{
	return true;
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	FBullCowCount BullCowCount;

	// get word lengths
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessWordLength = Guess.length();

	// loop through all letters in the hidden word
	for (int32 HChar = 0; HChar < HiddenWordLength; HChar++) 
	{
		// loop through all letters in the guess
		for (int32 GChar = 0; GChar < GuessWordLength; GChar++) 
		{
			// check if any of the letters match
			if (Guess[GChar] == MyHiddenWord[HChar]) 
			{
				if (HChar == GChar) // if same place, increment Bulls
				{
					BullCowCount.Bulls++;
				}
				else // increment Cows
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
		// compare letters against the hidden word

	return BullCowCount;
}

