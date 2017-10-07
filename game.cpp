#include <bits/stdc++.h>
using namespace std;


class linked_list
{
private:
	struct node {
		char data[100];
		node* next;
	};

	node* head;

	int size;

public:
	linked_list() {
		size = 0;
		head = NULL;
	}

	void push(char x[]) {
		node* temp = new node;
		strcpy(temp->data, x);
		temp -> next = head;
		head = temp;
		size++;
	}

	void show() {
		node* temp = head;
		while (temp!=NULL) {
			cout << temp -> data << "\n";
			temp = temp -> next;
		}
	}

	int getSize() {
		return size;
	}

	char* get(int idx) {
		node* temp = head;
		int i = 0;
		while (temp!=NULL && i < idx) {
			temp = temp->next;
			i++;
		}

		return temp->data;
	}

	int contains(char x[]) {
		node* temp = head;
		while (temp!=NULL) {
			if (!strcmp(temp -> data, x))
				return 1;
			temp = temp -> next;
		}
		return 0;
	}
};

class Hangman
{
private:
	char* word;
	char* letters_used;
	linked_list words;
	void getWord();
	void letters_used_so_far();
	int contains(char*, char);
	int guessed();
	char* temp_string(char);

public:
	Hangman();
	void rules();
	void beginGame();
};

void Hangman::getWord() {
	int size = words.getSize();
	if (words.getSize() == 0) {
		ifstream fin("words.txt", ios::in);
		char word[100];
		while(!fin.eof()) {
			fin >> word;
			words.push(word);
		}
		fin.close();
	}
	size = words.getSize();
	srand(time(NULL));
	int x = rand()%size;
	word = words.get(x);
}

void Hangman::letters_used_so_far() {
	int len = strlen(letters_used);
	for (int i = 0; i < len; i++)
		cout << letters_used[i] << ", ";
}

int Hangman::contains(char x[], char ch) {
	int len = strlen(x);
	for (int i = 0; i < len; i++)
		if (x[i] == ch)
			return 1;

	return 0;
}

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
			beginGame();
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

void Hangman::beginGame() {
	getWord();
	int wrong_guesses = 0;
	letters_used = new char[26];
	strcpy(letters_used, "");

	while (wrong_guesses < 6) {
		cout << "\nGuess a letter\n";
		cout << "Letters used so far: "; letters_used_so_far();
		if (guessed()) {
			cout << "\n\n";
			cout << "You guessed it right! The word is: " << word << endl << endl;
			break;
		}

		cout << "->";

		char a;
		cin >> a;
		if (!isalpha(a)) {
			cout << "\n\nInvalid input." << endl;
		}

		else if (contains(letters_used, tolower(a))) {
			cout << "\nThe letter has already been used!" << endl;
		}

		else {
			char temp[2];
			temp[0] = tolower(a);
			temp[1] = '\0';
			strcat(letters_used, temp);
			if (contains(word, tolower(a)))
				cout << "\nWell guessed!" << endl;
			else {
				wrong_guesses++;
				if (wrong_guesses == 6) {
					cout << "You made 6 wrong guesses! GAME OVER." << endl;
					cout << "The word is: " << word << endl << endl;
					break;
				}

				cout << "\nWrong Guess! ";
				cout << (6 - wrong_guesses) << " more wrong guesses left!" << endl;
			}
		}
	}

	cout << "Want to play again? (y/[n])\n";
	char ch;
	cin >> ch;
	
	if (tolower(ch) == 'y')
		beginGame();
	else {
		cout << "Have a nice day!";
		exit(0);
	}
}

int Hangman::guessed() {
	int m = strlen(letters_used);
	int n = strlen(word);
	int len = 0;

	char string[100];
	strcpy(string, "");

	for (int i = 0; i < n; i++) {
		if (contains(letters_used, word[i])) {
			len++;
			char temp[2];
			temp[0] = word[i];
			temp[1] = '\0';
			strcat(string, temp); 
		}
		else {
			strcat(string, "?");
		}
	}

	if (len == n)
		return 1;

	cout << "\nWord guessed so far: " << string << endl;
	return 0;
}

int main()
{
	Hangman game;
	
}