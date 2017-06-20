class Hangman():
	
	def __init__(self):
		print "Welcome! Press (1) to begin the game, press (2) to exit."
		choice = raw_input("->")

		if choice == '1':
			print "Let's begin!"
			self.rules()
			self.beginGame()

		elif choice == '2':
			print "Have a nice day!"
			exit()

		else:
			print "Invalid input."
			self.__init__()

	def rules(self):
		print "Rules:\n"
		print "Guess the right word by guessing the letters."
		print "6 wrong guesses and the game is over."
			

game = Hangman()