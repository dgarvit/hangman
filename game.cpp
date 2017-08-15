#include <iostream>
using namespace std;

class Hangman
{
public:
	Hangman();
	void rules();
	char* beginGame();
};

Hangman::Hangman() {
	cout << "Welcome! Press (1) to begin the game, press (2) to exit.";
	cout << "\n->";
	char choice;
	cin >> choice;
	// press any key to continue
	switch(choice) {
		case '1':
			cout << "Let's begin!\n";
			rules();
			char *word = beginGame();
			cout << " \n\n" << word << "\n\n";
			//core(word);
			break;

		case '2':
			cout << "Have a nice day!";
			exit(0);
	}
}

void Hangman::rules() {
	cout << "Rules:\n";
	cout << "Guess the right word by guessing the letters.\n";
	cout << "6 wrong guesses and the game is over.\n\n";
}

char* Hangman::beginGame() {
	return "word";
}

int main()
{
	Hangman game;
	
}