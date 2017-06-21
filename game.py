from random import randint

class Hangman():
	
	def __init__(self):
		print "Welcome! Press (1) to begin the game, press (2) to exit."
		choice = raw_input("->")

		if choice == '1':
			print "Let's begin!\n"
			self.rules()
			word = self.beginGame()
			self.core(word)

		elif choice == '2':
			print "Have a nice day!"
			exit()

		else:
			print "Invalid input."
			self.__init__()


	def rules(self):
		print "Rules:\n"
		print "Guess the right word by guessing the letters."
		print "6 wrong guesses and the game is over.\n\n"
		raw_input()


	def beginGame(self):
		file = open("words.txt", "r")
		words = file.readlines()
		file.close()
		word = list(words[randint(0, len(words) - 1)].lower())
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
			print "Guess a letter"
			print "Letters used so far: ", letters_used
			if self.guessed(word, letters_used):
				print "\n\nYou guessed it right! The word is:", ''.join(word)
				self.playAgain()
			a = raw_input('->').lower()

			if len(a) > 1 or not a.isalpha():
				print "Invalid input.\n"

			elif a in letters_used:
				print "Never played before? This letter has already been used!\n"

			else:
				letters_used.append(a)
				if a in word:
					print "Well guessed!\n"
				else:
					wrong_guesses += 1
					if wrong_guesses == 6:
						print "\n\nSo mean of you, you let the man hang! The word is:", ''.join(word)
						self.playAgain()

					print 6-wrong_guesses, "more wrong guesses and the man will be hanged!\n"
			raw_input()


	def playAgain(self):		
		print "\nWanna play again? Press (1). Press any other key to exit."
		a = raw_input('->')
		print "\n"
		if a == '1':
			word = self.beginGame()
			self.core(word)

		else:
			print "\n\nHave a nice day!"
			exit()

			

game = Hangman()