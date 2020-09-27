import pygame
from hardware.communicator import Communicator
from hardware.keyboard import Keyboard
from hardware.screen import Screen
from hardware.sound import Sound

from panels import welcome

class Emulator:
	def __init__(self):
		self.communicator = Communicator()
		self.screen = Screen()
		self.keyboard = Keyboard()
		self.sound = Sound()

		self.communicator.connect()

	def tick(self, surf, events, panels):
		# communication
		self.communicator.send({
			'content': ['frame'],
			'frame': {
				'keystate': self.keyboard.getPressed(),
			},
		})
		response = self.communicator.recv()
		if 'frame' in response['content']:
			self.sound.onRecv(response['frame']['sound'])
			self.screen.onRecv(response['frame']['graphics'])

		# ui
		for e in events:
			if e.type == pygame.QUIT:
				panels.clear()
			elif e.type == pygame.KEYUP:
				if e.key == pygame.K_ESCAPE:
					panels.clear()
					panels.append(welcome.Welcome())
		self.screen.draw(surf)
