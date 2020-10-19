# Chip8-Emulator
# Version 0.0
#
# Creators
# Nathan Luke Peters    |    Founding Member
#                       |    Lead Developer
#
# Dyllan Matthews       |    Founding Member
#                       |    Prototyping + Design
#
# licenced under GNU GPL

from gui.text import Text
from gui.button import Button
from gui.rectangle import Rectangle
from gui.colors import *
from gui.util import context_switcher

from panels import welcome

class Credits:
    def __init__(self):
        self.next = lambda panels: None
        switch_to = context_switcher(self)
        self.elements = [
            Rectangle(
                (0.00, 0.00, 1.00, 1.00),
                [BLACK],
            ),
            Text(
                "CHIP8 Emulator Version 0.0",
                (0.0, 0.05, 1.0, 0.08),
                [GREEN],
            ),
            Text(
                "Contributors",
                (0.00, 0.20, 1.0, 0.08),
                [GREY],
            ),
            Text(
                "chip8-emulator is licensed under GNU GPL",
                (0.00, 0.94, 1.0, 0.04),
                [GREY],
            ),
            Button(
                "X",
                (0.90, 0.02, 0.08, 0.08),
                [BLACK, GREY_DARK, None, GREY_BLACK, blend(GREY_BLACK,BLACK)],
                switch_to(welcome.Welcome),
            )
        ]

        author_stats = [
            ("Nathan Luke Peters", ["Founding member", "Lead Developer"]),
            ("Dylan Matthews", ["Founding Member", "Prototyping + Design"]),
        ]
        y = 0.40
        h = 0.06
        sp = 0.09
        ep = 0.09
        for (name, roles) in author_stats:
            self.elements.append(Text(
                name,
                (0.12, y, 0.35, h),
                [GREY_LIGHT, BLACK],
                "right",
            ))

            if len(roles) == 0:
                y += sp

            for role in roles:
                self.elements.append(Text(
                    role,
                    (0.53, y, 0.44, h),
                    [GREY, BLACK],
                    "left",
                ))
                y += sp
            y += ep

    def tick(self, surf, events, panels):
        for el in self.elements:
            el.update(surf, events)

        self.next(panels)
