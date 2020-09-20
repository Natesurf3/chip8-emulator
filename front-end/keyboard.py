class Keyboard():
	def __init__(self, pygame):
		self.pygame = pygame
		self.keypresses = []
		self.watchedKeys = [pygame.K_0, pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4, pygame.K_5, pygame.K_6, pygame.K_7, pygame.K_8, pygame.K_9, pygame.K_a, pygame.K_b, pygame.K_c, pygame.K_d, pygame.K_e, pygame.K_f]

	def getKeys(self):
		keys = self.pygame.key.get_pressed()

		watchedKeysPressed = []
		for key in self.watchedKeys:
			if keys[key]:
				name = self.pygame.key.name(key)
				watchedKeysPressed.append(name)

		return watchedKeysPressed