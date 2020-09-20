from config import SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_COLOR, PIXEL_COLOR, PIXEL_DIMENSION


class Screen:
	def __init__(self, pygame, screen):
		self.pixels = [False] * (SCREEN_HEIGHT * SCREEN_WIDTH)
		self.pygame = pygame
		self.screen = screen

	def setPixels(self, new_pixels):
		if len(new_pixels) == (SCREEN_WIDTH * SCREEN_HEIGHT):
			self.pixels = new_pixels
		else:
			raise Exception("Number of pixels sent does not match screen")

	def display(self):
		for i in range(len(self.pixels)):
			pix_val = self.pixels[i]
			pix_x = i % SCREEN_WIDTH
			pix_y = int(i / SCREEN_WIDTH)
			self.display_pixel(pix_val, pix_x, pix_y)

	def setPixel(self, pixel_value, x, y):
		self.pixels[y*SCREEN_WIDTH + x] = pixel_value

	def display_pixel(self, pixel_value, x, y):
		self.pygame.draw.rect(self.screen, PIXEL_COLOR if pixel_value else SCREEN_COLOR, [x * PIXEL_DIMENSION, y * PIXEL_DIMENSION, PIXEL_DIMENSION, PIXEL_DIMENSION])

