class Hangman():
	
	def __init__(self):
		print "Welcome! Press (1) to begin the game, press (2) to exit."
		choice = raw_input("->")

		if choice == '1':
			print "Let's begin!"
			self.beginGame()

		elif choice == '2':
			print "Have a nice day!"
			exit()

		else:
			print "Invalid input."
			self.__init__()
		

game = Hangman()