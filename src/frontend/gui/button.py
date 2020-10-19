import pygame
from gui.boundry import convert_to_pxbound
from gui.colors import *
from gui.text import Text
from gui.rectangle import Rectangle
# colors = (text=foreground, background, border, hover_bgc, press_bgc)

class Button:
    def __init__(self, text, bound, colors=[], on_click=lambda: None):
        self.colors = combine_left(
            [BLACK, GREY_LIGHT, BLACK, GREY, GREY_DARK],
            colors
        )
        self.text = Text(text, bound, colors[:1])
        self.rect = Rectangle(bound, colors[1:2], bound[3]*0.1)

        self.bound = bound
        self.on_click = on_click

        self.is_press = False
        self.is_hover = False
        self.mouseloc = None
        self.mousedown = False

    def update(self, surf, events):
        pxbound = convert_to_pxbound(self.bound, surf)

        for e in events:
            if e.type == pygame.MOUSEMOTION:
                self.mouseloc = e.pos
                self.is_hover = pygame.Rect(pxbound).collidepoint(e.pos)
            elif e.type == pygame.MOUSEBUTTONDOWN:
                self.mousedown = True
                self.is_press = self.is_hover
            elif e.type == pygame.MOUSEBUTTONUP:
                self.mousedown = False
                self.is_press = False
                if self.is_hover:
                    self.on_click(self)

        if self.is_press:   self.rect.colors[0] = self.colors[4]
        elif self.is_hover: self.rect.colors[0] = self.colors[3]
        else:               self.rect.colors[0] = self.colors[1]

        self.rect.update(surf, events)
        self.text.update(surf, events)
