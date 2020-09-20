class Sound():
	def __init__(self, pygame):
		self.musicPlayer = pygame.mixer.music
		self.musicPlayer.load('beep.wav')
		self.isPlaying = False

	def play(self):
		if not self.isPlaying:
			self.musicPlayer.play(-1)
			self.isPlaying = True

	def stop(self):
		if self.isPlaying:
			self.musicPlayer.stop()
			self.isPlaying = False