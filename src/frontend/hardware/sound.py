import pygame

class Sound():
	def __init__(self):
		self.music_player = pygame.mixer.music
		self.is_playing = False
		self.music_player.load('./hardware/beep.wav')

	def onRecv(self, re):
		[self.stop, self.start][re]()

	def start(self):
		if not self.is_playing:
			self.music_player.play(-1)
			self.is_playing = True

	def stop(self):
		if self.is_playing:
			self.music_player.stop()
			self.is_playing = False
