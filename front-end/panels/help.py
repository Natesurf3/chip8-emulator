#                         CHIP8 Emulator                         |
#                             Manual                             |
#                                                                |
#  How it works                                                  |
#      Chip8 Emulator works by simulating a virtual computer     |
#    inside of your computer. That virtual computer has its own  |
#    memory, monitor, CPU, registers, and instruction set. CHIP8 |
#    emulator lets you interact with this virtual computer to    |
#    access programs that run on this virtual computer. Without  |
#    Chip8 Emulator or some substitute, you wouldn't be able to  |
#    run these programs because they were never designed to run  |
#    on the types of computers we see in 2020.                   |
#________________________________________________________________/


import pygame
from gui.text import TextBox
from gui.rectangle import Rectangle
from gui.colors import *
from gui.button import Button
from gui.util import context_switcher

from panels import welcome
# charwidth = 60

def pad(st, length):
    while len(st) < length:
        st += " "
    return st

class Help:
    def __init__(self):
        self.text = [
            "User Manual",
            "How it works",
            "  Chip8 Emulator works by simulating a virtual computer",
            "inside of your computer. That virtual computer has its own",
            "memory, monitor, CPU, registers, and instruction set. CHIP8",
            "emulator lets you interact with this virtual computer to",
            "access programs that run on this virtual computer. Without",
            "Chip8 Emulator or some substitute, you wouldn't be able to",
            "run these programs because they were never designed to run",
            "on the types of computers we see in 2020.",
        ]

        self.next = lambda button: None
        switch_to = context_switcher(self)
        bgc = blend(BLUE, BLACK, 1.0),
        self.elements = [
            Rectangle(
                (0.00, 0.00, 1.00, 1.00),
                bgc,
            ),
            TextBox(
                "User Manual",
                (0.00, 0.09, 1.00, 0.115),
                [GREY, bgc],
                "center"
            ),
            TextBox(
                "How it works",
                (0.15, 0.22, 1.00, 0.06),
                [GREY_DARK, bgc],
                "left",
            ),
            Button(
                "X",
                (0.90, 0.02, 0.08, 0.08),
                [BLACK, GREY_DARK, None, GREY_BLACK, blend(GREY_BLACK,BLACK)],
                switch_to(welcome.Welcome),
            ),
        ]

        for i in range(2, len(self.text)):
            self.elements.append(TextBox(
                pad(self.text[i], 60),
                (0.20, 0.38+(i-3)*0.07, 0.60, 0.06),
                [GREY_DARK, bgc],
                "left"
            ))



    def tick(self, surf, events, panels):
        for el in self.elements:
            el.update(surf, events)

        self.next(panels)
