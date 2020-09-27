from gui.button import Button
from colors import *
from gui.boundry import convert_to_rlpos

class Slider:
    # bounds: (x, y, width, height)
    # range: (min, max)
    def __init__(self, bounds, range, on_move=lambda: None):
        self.bounds = bounds
        self.range = range
        self.on_move = on_move

        self.val =

        (x,y,w,h) = bounds
        self.elements = [
            Button(
                "",
                (x, y+h*0.35, w, h*0.30),
                self.slide_move,
            ),
            Button(
                "",
                (x+w*0.45, y, w*0.10, h)),
                self.slide_move,
            )
        ]

    def slide_move(button):
        loc = convert_to_rlpos(button.mouseloc)
        rel_x = loc[0]-self.bounds[0]
        self.val = rel_x/self.bounds[2] * (range[1]-range[0]) + range[0]

        b = self.elements[0].bounds
        b[0] = loc[0]-b[2]/2

    def update(self, surf, events):
        for el in self.elements:
            el.update(surf, events)

        for el in self.elements:
            if el.is_press:
