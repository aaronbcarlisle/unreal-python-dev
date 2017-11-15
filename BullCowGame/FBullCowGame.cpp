#include <iostream>
#include "FBullCowGame.h"

// constructor
FBullCowGame::FBullCowGame() { Reset(); }

// getters
int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

// constants
bool FBullCowGame::IsGameWon() const { return true; }
bool FBullCowGame::CheckGuessValidity(FString) const { return true; }

void FBullCowGame::Reset()
{
	// constants
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	// reset members
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
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

	return BullCowCount;
}

