from pygame import font
from pygame import transform
from pygame import draw

from gui.boundry import convert_to_pxbound
from gui.colors import *

# colors = (text=foreground, background, border)
# align = "left" or "center" or "right"
class TextBox:
    def __init__(self, text, bound, colors=[], align="center"):
        self.colors = [GREEN, BLACK, None]
        for i in range(len(colors)):
            self.colors[i] = colors[i]
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
        self._text_surf = self.font.render(self._text, True, self.colors[0], self.colors[1]).convert()


    def update(self, surf, events):
        pxbound = convert_to_pxbound(self.bound, surf)

        # update the font
        self.setSize(pxbound[3])

        # measure font
        init_t_size = (
            self._text_surf.get_width(),
            self.font.get_height()*1.3,
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
        if self.colors[1] != None:
            draw.rect(surf, self.colors[1], pxbound)

        if self.colors[2] != None:
            draw.rect(surf, self.colors[2], pxbound, 1+int(pxbound[3]/35))

        text_surf = transform.scale(self._text_surf, t_size)
        surf.blit(text_surf, t_loc)
