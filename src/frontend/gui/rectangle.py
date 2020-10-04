import pygame
from gui.boundry import convert_to_pxbound

# not to be confused with pygame.rect
class Rectangle:
    def __init__(self, bound, color, width=0):
        self.bound = bound
        self.color = color
        self.width = width

    def update(self, surf, events):
        pygame.draw.rect(
            surf,
            self.color,
            convert_to_pxbound(self.bound, surf),
            self.width
        )
