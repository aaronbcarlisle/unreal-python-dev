#include "FBullCowGame.h"

// getters
int FBullCowGame::GetMaxTries() { return MyMaxTries; }
int FBullCowGame::GetCurrentTry() { return MyCurrentTry; }

void FBullCowGame::Reset()
{
	return;
}

bool FBullCowGame::IsGameWon()
{
	return true;
}

bool FBullCowGame::CheckGuessValidity(std::string)
{
	return true;
}
