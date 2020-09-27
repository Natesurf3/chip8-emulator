import pygame
from gui.boundry import convert_to_pxbound
from gui.colors import *
from gui.text import TextBox
# colors = (text=foreground, background, border, hover_bgc, press_bgc)

class Button:
    def __init__(self, text, bound, colors=[], on_click=lambda: None):
        self.colors = [BLACK, GREY_LIGHT, BLACK, GREY, GREY_DARK]
        for i in range(len(colors)):
            self.colors[i] = colors[i]
        self.text_box = TextBox(text, bound, colors[:3])

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

        if self.is_press:   self.text_box.setColor(1, self.colors[4])
        elif self.is_hover: self.text_box.setColor(1, self.colors[3])
        else:               self.text_box.setColor(1, self.colors[1])

        self.text_box.update(surf, events)
