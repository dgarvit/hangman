from random import randint
from os import system
from time import sleep

class Hangman():
	
    def __init__(self):
        
        system('cls')   #Added so that the screen comes fresh if input is invalid
        print "Welcome! Press (1) to begin the game, press (2) to exit."
        choice = raw_input("->")

        if choice == '1':
            system('cls')
            print "Let's begin!\n"
            word = self.beginGame()
            self.core(word)

        elif choice == '2':
            print "\nHave a nice day!"
            sleep(2)
            exit()

        else:
            print "\nInvalid input."
            sleep(1)
            self.__init__()

    def beginGame(self):
        file = open("words.txt", "r")
        words = file.readlines()
        file.close()
        word = list(words[randint(0, len(words) - 1)])
        if word[-1] == '\n':
            del word[-1]
        return word


    def guessed(self, word, letters_used):
        s = ""
        for l in word:
            if l in letters_used:
                s+=l
            else:
                s+='?'
        print "Word guessed so far: ", s
        if '?' in s:
            return False
        return True


    def core(self, word):
        wrong_guesses = 0
        letters_used = []

        while wrong_guesses < 6:
            system('cls')
            
            print "Rules:\n"
            print "Guess the right word by guessing the letters."
            print "6 wrong guesses and the game is over.\n\n"
            
            print "Your game:\n"
            print 6-wrong_guesses, "more wrong guesses and the man will be hanged!\n"
            print "Guess a letter"
            print "Letters used so far: ", letters_used
            if self.guessed(word, letters_used):
                print "\n\nYou guessed it right! The word is:", ''.join(word)
                sleep(3)                
                self.playAgain()
            a = raw_input('->')
            a = a.lower()
            
            if len(a) > 1 or not a.isalpha():
                print "\nInvalid input.\n"

            elif a in letters_used:
                print "\nNever played before? This letter has already been used!\n"

            else:
                letters_used.append(a)
                if a in word:
                    print "\nWell guessed!"
                else:
                    print "\nYou want me hanged eh?"
                    wrong_guesses += 1
                    if wrong_guesses == 6:
                        print "\n\nSo mean of you, you let the man hang! The word is:", ''.join(word)
                        sleep(2)                        
                        self.playAgain()
            sleep(1)


    def playAgain(self):		
        system('cls')        
        print "Wanna play again? Press (1). Press any other key to exit."
        a = raw_input('->')
        print "\n"
        if a == '1':
            word = self.beginGame()
            self.core(word)

        else:
            print "Have a nice day!"
            sleep(1.5)
            exit()

			

game = Hangman()
