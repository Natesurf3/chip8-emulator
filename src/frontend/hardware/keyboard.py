import pygame

class Keyboard():
	def __init__(self):
		self.watch_list = [
			pygame.K_0, pygame.K_1, pygame.K_2, pygame.K_3, pygame.K_4,
			pygame.K_5, pygame.K_6, pygame.K_7, pygame.K_8, pygame.K_9,
			pygame.K_a, pygame.K_b, pygame.K_c, pygame.K_d, pygame.K_e,
			pygame.K_f
		]

	def getKeystate(self):
		keystate = [False] * 16
		pygame.event.pump()
		all_keystate = pygame.key.get_pressed()
		for i in range(16):
			if all_keystate[self.watch_list[i]]:
				keystate[i] = True
#		print("keystate"+str(keystate))
		return keystate
