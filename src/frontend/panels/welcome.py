#     CHIP8 Emulator
#
#         |Start|
#        |Settings|
#          |Help|
#         |Credits|
#

from gui.text import Text
from gui.rectangle import Rectangle
from gui.button import Button
from gui.colors import *
from gui.util import context_switcher

from panels.explorer import Explorer
from panels.settings import Settings
from panels.help import Help
from panels.credits import Credits

class Welcome:
    def __init__(self):
        self.next = lambda panels: None

        switch_to = context_switcher(self)
        self.elements = [
            Rectangle(
                (0,0,1,1),
                [BLACK],
            ),
            Text(
                "CHIP8 Emulator",
                (0.35, 0.05, 0.30, 0.10),
            ),
            Button(
                "Start",
                (0.25, 0.25, 0.50, 0.10),
                [GREEN, BLACK],
                switch_to(Explorer.try_from_prompt),
            ),
            Button(
                "Settings",
                (0.25, 0.40, 0.50, 0.10),
                [GREEN, BLACK],
                switch_to(Settings),
            ),
            Button(
                "Help",
                (0.25, 0.55, 0.50, 0.10),
                [GREEN, BLACK],
                switch_to(Help),
            ),
            Button(
                "Credits",
                (0.25, 0.70, 0.50, 0.10),
                [GREEN, BLACK],
                switch_to(Credits),
            ),

#            Button(
#                "X",
#                (0.90, 0.02, 0.08, 0.08),
#                [BLACK, GREY_DARK, None, GREY_BLACK, blend(GREY_BLACK,BLACK)],
#                switch_to(None),
#            ),
        ]

    def tick(self, surf, events, panels):
        for el in self.elements:
            el.update(surf, events)

        self.next(panels)
