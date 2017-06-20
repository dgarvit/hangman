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


	def beginGame(self):
		file = open("words.txt", "r")
		words = file.readlines()
		file.close()
		word = list(words[randint(0, len(words) - 1)])
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


	def core(self, word):
		wrong_guesses = 0
		letters_used = []

		while wrong_guesses < 6:
			print "Guess a letter"
			print "Letters used so far: ", letters_used
			self.guessed(word, letters_used)
			a = raw_input('->')

			if len(a) > 1 or not a.isalpha():
				print "Invalid input.\n"

			elif a in letters_used:
				print "Never played before? This letter has already been used!\n"

			else:
				letters_used.append(a)
				if a in word:
					print "Well guessed!"
				else:
					wrong_guesses += 1
					print 6-wrong_guesses, "more wrong guesses and the man will be hanged!"

			

game = Hangman()