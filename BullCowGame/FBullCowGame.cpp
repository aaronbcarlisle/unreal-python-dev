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
BullCowCount FBullCowGame::SubmitGuess(FString)
{
	// increment the turn number
	MyCurrentTry++;

	// setup a return variable
	BullCowCount BullCowCount;

	// loop through all letters in the guess
		// compare letters against the hidden word

	return BullCowCount;
}

