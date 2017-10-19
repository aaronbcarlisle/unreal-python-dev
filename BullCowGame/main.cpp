#include <iostream>
#include <string>

// namespaces
using namespace std;

// declarations
void PrintIntro();
string GetGuess();
void PrintGuess(string Guess);

int main()
{
	PrintIntro();

	// loop through turns.
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		// get guess and print back
		PrintGuess(GetGuess());
	}

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
