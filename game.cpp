#include <bits/stdc++.h>
using namespace std;


int logged_in = 0;	// flag to check if user is logged in or not

class User
{
private:
	char name[50];
	char email[50];
	char password[50];
	int win;
	int loss;

	void modify();

public:
	User() {
		win = 0;
		loss = 0;
	}

	int create_new_user(char name[], char email[], char password[]);
	int login(char email[], char password[]);
	void show_data(int show_name);
	void won() {
		win++;
		modify();
	}
	void lost() {
		loss++;
		modify();
	}
} user;

void User::modify() {
	fstream fil;
	fil.open("user.dat",ios::in| ios::out|ios::binary);
	User u;
	fil.read((char*)&u, sizeof(u));
	while (!fil.eof()) {
		if (!strcmp(u.email, user.email)) {
			fil.seekg(0,ios::cur);
			fil.seekp(fil.tellg() - sizeof(user));
			fil.write((char*)&(user), sizeof(user));
			break;
		}
		fil.read((char*)&u, sizeof(u));
	}

	fil.close();
}

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
	fout.write((char*)&u, sizeof(u));
	fin.close();
	fout.close();
	return 1;							// successfully created
}

int User::login(char email[], char password[]) {
	if (logged_in == 1)
		return 1;
	ifstream fin;
	fin.open("user.dat", ios::in);
	User u;
	while (!fin.eof()) {
		fin.read((char*)&u, sizeof(u));
		if (!strcmp(u.email, email)) {
			fin.close();
			if (!strcmp(u.password, password)) {
				logged_in = 1;
				user = u;
				return 1;	// successful login
			}
			else
				return 0;	// incorrect password
		}
	}

	fin.close();
	return -1;				// user does not exist
}

void User::show_data(int show_name) {
	cout << "\n\n\n";
	if (show_name) {
		cout << "Name: " << name << endl;
		cout << "Email: " << email << endl;
	}
	cout << "Total games played: " << win + loss << endl;
	cout << "Wins: " << win << endl;
	cout << "Losses: " << loss << endl;
	cin.ignore();
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

void login() {
	User u;
	while (!logged_in) {
		cout << "\n\nEnter (1) to login or (2) to create new user";
		cout << "\n-> ";
		char ch;
		cin >> ch;
		switch(ch) {
			case '2':
			{
				char name[50], email[50], password[50];
				cout << "\nEnter name: ";
				cin >> name;
				cout << "\nEnter email: ";
				cin >> email;
				cout << "\nEnter password: ";
				cin >> password;

				int status = u.create_new_user(name, email, password);
				switch(status) {
					case 1:
						cout << "\n\nUser registered successfully";
						break;
					default:
						cout << "\n\nEmail already exists!";
						break;
				}
				break;
			}

			case '1':
			{
				char email[50], password[50];
				cout << "\nEnter email: ";
				cin >> email;
				cout << "\nEnter password: ";
				cin >> password;

				int status = u.login(email, password);
				switch (status) {
					case 1:
						cout << "\nHi ";
						user.show_data(1);
						break;

					default:
						cout << "\n\nIncorrect email or password.";
				}
				break;
			}
		}
	}
}

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
	while (!logged_in) {
		cout << "\n\nYou are not logged in!";
		login();
	}
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
			user.won();
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
					user.lost();
					cout << "The word is: " << word << endl << endl;
					break;
				}

				cout << "\nWrong Guess! ";
				cout << (6 - wrong_guesses) << " more wrong guesses left!" << endl;
			}
		}
	}

	user.show_data(0);
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