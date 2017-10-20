#include <iostream>
#include <string>

// namespaces
using namespace std;

// declarations
void PrintIntro();
void PlayGame();
string GetGuess();
void PrintGuess(string Guess);
bool AskToPlayAgain();


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
	constexpr int WORD_LENGTH = 8;

	// intro
	cout << "Welcome to Bulls and Cows, a fun word game\n";
	cout << "Can you guess the " << WORD_LENGTH;
	cout << " letter isogram I'm thinking of?\n";
	cout << endl;
}

void PlayGame()
{
	// loop through turns.
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		// get guess and print back
		PrintGuess(GetGuess());
	}
}

string GetGuess() 
{
	// ask for guess
	string Guess = "";
	cout << "Enter your guess: ";

	// get guess
	getline(cin, Guess);
	
	return Guess;
}

void PrintGuess(string Guess)
{
	// repeat the guess back
	cout << "Your guess was: " << Guess << endl;
    cout << endl;
}

bool AskToPlayAgain()
{
	// ask to play again
	string Response = "";
	cout << "Do you want to play again (y/n)? ";

	// get response
	getline(cin, Response);
    cout << endl;

	// return bool (y for true, anything else for false)
	return (Response[0] == 'y') || (Response[0] == 'Y');
}
