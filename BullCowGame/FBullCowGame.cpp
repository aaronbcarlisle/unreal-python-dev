#include <iostream>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

// constructor
FBullCowGame::FBullCowGame() { Reset(); }

// getters
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	// use a map to define the difficulty of the game 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const 
{ 
	if (!IsIsogram(Guess)) // if the guess isn't an isogram, 
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase, 
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

void FBullCowGame::Reset()
{
	// constants
	const FString HIDDEN_WORD = "planet";

	// reset members
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a valid guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
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

	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as an isogram
	if (Word.length() <= 1) { return true; }

	// setup our map
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case 
		if (LetterSeen[Letter]) 
		{
			return false; // we do NOT have an isogram
		}
		else
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false; // 
		}
	}

	return true; // if all letters are lowercase, move on
}

