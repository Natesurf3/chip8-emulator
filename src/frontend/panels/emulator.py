import pygame
from communicator.communicator import Communicator
from hardware.keyboard import Keyboard
from hardware.screen import Screen
from hardware.sound import Sound
from panels import welcome

# persistant connection to server
com = Communicator()
com.connect()

class Emulator:
	def __init__(self, path):
		self.communicator = com
		self.screen = Screen()
		self.keyboard = Keyboard()
		self.sound = Sound()

		self.communicator.send({
			'content': ['state'],
			'state': 'start',
			'start_path': path,
		})
		self.communicator.recv()

	def tick(self, surf, events, panels):
		# communication
		
		self.communicator.send({
			'content': ['frame'],
			'frame': {
				'keystate': self.keyboard.getKeystate(),
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
					self.communicator.send({
						'content': ['state'],
						'state': 'stop',
					})
					self.communicator.recv()
					panels.clear()
					panels.append(welcome.Welcome())
		self.screen.draw(surf)
