import pygame
on_color = (0, 255, 0)
surround_color = (0, 125, 0)
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
		self.pixels.clear()
		self.pixels.extend(re)

	def draw(self, surf):
		pix_size = surf.get_height() // self.size[1]
		# pygame.draw.rect(surf, (0,0,0), (0,0,pix_size*self.size[0], pix_size*self.size[1]))

		on_surf = pygame.Surface((pix_size,pix_size)).convert()
		off_surf = pygame.Surface((pix_size,pix_size)).convert()
		pygame.draw.rect(on_surf, surround_color, (0, 0, pix_size, pix_size))
		pygame.draw.rect(on_surf, on_color, (1, 1, pix_size-2, pix_size-2))
		pygame.draw.rect(off_surf, off_color, (0, 0, pix_size, pix_size))


		for (x, y, ix) in xy_iter(self.size):
			img = [off_surf, on_surf][self.pixels[ix]]
			loc = (pix_size*x, pix_size*y)
			surf.blit(img, loc)
