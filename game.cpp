#include <bits/stdc++.h>
using namespace std;


class User
{
private:
	char name[50];
	char email[50];
	char password[50];
	int win;
	int loss;

public:
	User() {
		win = 0;
		loss = 0;
	}

	int create_new_user(char name[], char email[], char password[]);

	void show_data() {
		cout << name << endl;
		cout << email << endl;
		cout << win << endl;
		cout << loss << endl;
	}
};

int User::create_new_user(char name[], char email[], char password[]) {
	ifstream fin;
	ofstream fout;
	fin.open("user.dat", ios::in);
	fout.open("user.dat", ios::app);
	User u;
	while (!fin.eof()) {
		fin.read((char*)&u, sizeof(u));
		if (!strcmp(u.email, email)) {
			fin.close();
			fout.close();
			return -1;					// user already exists
		}
	}
	strcpy(u.name, name);
	strcpy(u.email, email);
	strcpy(u.password, password);
	u.show_data();
	fout.write((char*)&u, sizeof(u));
	fin.close();
	fout.close();
	return 1;							// successfully created
}


class linked_list
{
private:
	struct node {		// a node of linked list data
		char data[100];
		node* next;
	};

	node* head; 		// linked list head pointer

	int size;

public:
	linked_list() {
		size = 0;
		head = NULL;
	}

	void push(char x[]) {		// function to push data to linked list
		node* temp = new node;
		strcpy(temp->data, x);
		temp -> next = head;
		head = temp;
		size++;
	}

	void show() {				// function to print all list data
		node* temp = head;
		while (temp!=NULL) {
			cout << temp -> data << "\n";
			temp = temp -> next;
		}
	}

	int getSize() {				// function to get the size of list
		return size;
	}

	char* get(int idx) {		// function to get an element by index from the list
		node* temp = head;
		int i = 0;
		while (temp!=NULL && i < idx) {
			temp = temp->next;
			i++;
		}

		return temp->data;
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

void Hangman::getWord() {		// get a random word from the text file
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

void Hangman::letters_used_so_far() {	// print letters used so far
	int len = strlen(letters_used);
	for (int i = 0; i < len; i++)
		cout << letters_used[i] << ", ";
}

int Hangman::contains(char x[], char ch) {	// check if a given string contains a given letter
	int len = strlen(x);
	for (int i = 0; i < len; i++)
		if (x[i] == ch)
			return 1;

	return 0;
}

Hangman::Hangman() {	// constructor
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

void Hangman::rules() {		// game rules
	cout << "Rules:\n";
	cout << "Guess the right word by guessing the letters.\n";
	cout << "6 wrong guesses and the game is over.\n\n";
}

void Hangman::beginGame() {		// game handler
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
		beginGame();		// play again
	else {
		cout << "Have a nice day!";
		exit(0);
	}
}

int Hangman::guessed() {	// check if the word has been correctly guessed
	int m = strlen(letters_used);
	int n = strlen(word);
	int len = 0;

	char string[100];		// word guessed so far
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