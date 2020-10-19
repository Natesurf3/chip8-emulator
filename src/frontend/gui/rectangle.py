import pygame
from gui.boundry import convert_to_pxbound
from gui.colors import *

# not to be confused with pygame.rect
# colors = (background, border)
class Rectangle:
    def __init__(self, bound, colors, border=0):
        self.bound = bound
        self.colors = combine_left([BLACK, None], colors)
        self.border = border

    def update(self, surf, events):
        inner_bound = self.bound

        if self.border != 0 and self.colors[1] != None:
            pygame.draw.rect(
                surf,
                self.colors[1],
                convert_to_pxbound(self.bound, surf),
                0
            )
            inner_bound = [
                self.bound[0] + self.border,
                self.bound[1] + self.border,
                self.bound[2] - self.border,
                self.bound[3] - self.border,
            ]

        pygame.draw.rect(
            surf,
            self.colors[0],
            convert_to_pxbound(inner_bound, surf),
            0
        )
