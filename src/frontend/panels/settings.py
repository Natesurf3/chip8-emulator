# tick rate
# set fps
# show fps overlay

# anti-flicker
# screen size
# instruction set

from gui.text import Text
from gui.rectangle import Rectangle
from gui.colors import *
from gui.button import Button
from gui.util import context_switcher

from panels import welcome

class Settings:
    def __init__(self):
        self.next = lambda button: None
        switch_to = context_switcher(self)
        self.elements = [
            Rectangle(
                (0,0,1,1),
                [BLACK],
            ),
            Text(
                "Settings",
                (0.00, 0.05, 1.00, 0.10),
            ),
            Button(
                "X",
                (0.90, 0.02, 0.08, 0.08),
                [BLACK, GREY_DARK, None, GREY_BLACK, blend(GREY_BLACK,BLACK)],
                switch_to(welcome.Welcome),
            ),
        ]

    def tick(self, surf, events, panels):
        for el in self.elements:
            el.update(surf, events)

        self.next(panels)
