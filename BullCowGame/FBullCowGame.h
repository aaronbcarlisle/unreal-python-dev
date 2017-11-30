#pragma once
#include <string>

using FString = std::string;
using int32 = int;

// all values initialized to 0
struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

// strongly typed enum class
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
};

class FBullCowGame
{
public:
	// constructor
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 

	void Reset(); // TODO make a richer return 

	// counts bulls & cows, and increasing try # assuming valid guess
	FBullCowCount SubmitValidGuess(FString);

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
};