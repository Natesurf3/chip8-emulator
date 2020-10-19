from pygame import font
from pygame import transform
from pygame import draw

from gui.boundry import convert_to_pxbound
from gui.colors import *

class Text:
    def __init__(self, text, bound, colors=[], align="center"):
        self.colors = combine_left(
            [GREEN],
            colors
        )

        self.bound = bound
        self.align = align

        self.font_size = 30
        self._text = text
        self.reRender()

    def setText(self, text):
        if text != self._text:
            self._text = text
            self.reRender()

    def setColor(self, ix, val):
        if self.colors[ix] != val:
            self.colors[ix] = val
            self.reRender()

    def setSize(self, height):
        font_size = round(height * 1.00)
        if font_size != self.font_size:
            self.font_size = font_size
            self.reRender()

    def reRender(self):
        self.font = font.SysFont('freesans', self.font_size)
        self._text_surf = self.font.render(self._text, True, self.colors[0], None)
        self._text_surf = self._text_surf.convert_alpha()


    def update(self, surf, events):
        pxbound = convert_to_pxbound(self.bound, surf)

        # update the font
        self.setSize(pxbound[3])

        # measure font
        init_t_size = (
            self._text_surf.get_width(),
            self.font.get_height(), # *1.3
        )

        # scale to fit
        ratio = min(pxbound[2] / init_t_size[0], pxbound[3] / init_t_size[1])
        t_size = (
            round(init_t_size[0] * ratio),
            round(init_t_size[1] * ratio),
        )

        # position
        offset_mult = {"left":0, "center":0.5, "right":1}[self.align]
        t_loc = (
            round(pxbound[0] + (pxbound[2]-t_size[0]) * offset_mult),
            round(pxbound[1] + (pxbound[3]-t_size[1]) * 0.5),
        )

        # draw
        text_surf = transform.scale(self._text_surf, t_size)
        surf.blit(text_surf, t_loc)
