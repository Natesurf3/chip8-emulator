import pygame
import config
from screen import Screen
from backendConnection import Chip8EngineCEngineConnection
from keyboard import Keyboard
from sound import Sound

class FrontEnd:
	def __init__(self):
		# In a production environment, we would probably abstract out the library specific code.
		self.pygame = pygame
		self.pygame.init()
		self.screen = pygame.display.set_mode(config.size)

		self.gameScreen = Screen(self.pygame, self.screen)
		self.backEndConnection = Chip8EngineCEngineConnection()
		self.clock = pygame.time.Clock() # Clock would probably be a part of the same unit that enapsulates pygame and screen.
		self.beep = Sound(pygame)
		self.keyboard = Keyboard(pygame)
		self.running = False

	def _getNextScreen(self):
		return self.backEndConnection.receiveGraphics()

	def _displayNextScreen(self, next):
		self.gameScreen.setPixels(next)
		self.gameScreen.display()

	def _connect(self):
		self.backEndConnection.connect()

	def run(self):
		# This would also be abstracted out, but will keep in order to reduce codesize.
		self.running = True

		self._connect()

		while self.running:
			for event in pygame.event.get(): # Keypresses get processed here
				if event.type == pygame.QUIT:
					self.running = False

			# We grab the key state and pass to request.
			keysPressed = self.keyboard.getKeys()
			self.backEndConnection.sendRequest(keysPressed)
			response = self.backEndConnection.getReply()
			
			if response['payload']['sound']:
				self.beep.play()
			else:
				self.beep.stop()

			# nextScreen = self._getNextScreen()
			self._displayNextScreen(response['payload']['graphics'])

			self.pygame.display.flip()
			self.clock.tick(60)

		self.pygame.quit()


fe = FrontEnd()

fe.run()



