# browse filesystem to select rom

#          SELECT A ROM
#      -- /path-from-rom --
#   --------------------------
#         FOLD foldername
#         FOLD foldername
#
#         FILE filename
#     >>> FILE fname <<<
#         FILE the_entire_filena...

from gui.boundry import convert_to_pxbound
from gui.text import TextBox
from gui.colors import *
from gui.rectangle import Rectangle
from gui.util import context_switcher
from gui.button import Button

from panels import welcome
def clamp_str(st, length):
    if len(st) < length: return st
    else:                return st[:length-3]+"..."


class Explorer:
    def __init__(self):
        self.base_dir = "../emulator/resources/curated_rom"
        self.current_dir = self.base_dir

        self.next = lambda button: None
        switch_to = context_switcher(self)
        self.constant_elements = [
            Rectangle(
                (0.00, 0.00, 1.00, 1.00),
                BLACK,
            ),
            TextBox(
                "SELECT A ROM",
                (0.35, 0.05, 0.30, 0.10),
                [GREEN]
            ),
            TextBox(
                "-- <directory> --",
                (0.25, 0.20, 0.50, 0.07),
                [GREY_LIGHT],
            ),
            Button(
                "X",
                (0.90, 0.02, 0.08, 0.08),
                [BLACK, GREY_DARK, None, GREY_BLACK, blend(GREY_BLACK,BLACK)],
                switch_to(welcome.Welcome),
            ),

        ]

    def load_dir(self):
        self.folders = []
        self.files = []



    def tick(self, surf, events, panels):
        for e in self.constant_elements:
            e.update(surf, events)

        self.next(panels)
