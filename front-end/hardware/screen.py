import pygame
on_color = (0, 255, 0)
off_color = (0, 0, 0)
default_size = (64, 32)

def xy_iter(dim):
	for x in range(dim[0]):
		for y in range(dim[1]):
			yield (x, y, x+y*dim[0])

class Screen:
	def __init__(self):
		self.size = default_size
		self.pixels = [False] * (self.size[0] * self.size[1])

	def onRecv(self, re):
		assert(len(re) == self.size[0] * self.size[1])
		for (x, y, ix) in xy_iter(self.size):
			self.pixels[ix] = re[ix]

	def draw(self, surf):
		pix_size = surf.get_height() / self.size[1]
		for (x, y, ix) in xy_iter(self.size):
			color = [off_color, on_color][self.pixels[ix]]
			bound = [pix_size*x, pix_size*y, pix_size, pix_size]
			pygame.draw.rect(surf, color, bound)
