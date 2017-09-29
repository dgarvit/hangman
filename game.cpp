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
};

class Hangman
{
private:
	char* word;
	linked_list words;
	void getWord();

public:
	Hangman();
	void rules();
	char* beginGame();
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
			getWord();
			cout << " \n\n" << word << "\n\n";
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

}

int main()
{
	Hangman game;
	
}