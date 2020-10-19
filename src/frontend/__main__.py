import pygame

from panels.welcome import Welcome
from gui.tps import Tps

win_init_size = (1024, 512)
if __name__ == "__main__":
    pygame.init()
    pygame.font.init()

    surf = pygame.display.set_mode(win_init_size, pygame.RESIZABLE)
    tps = Tps(20)

    panels = []     # filter, clear, extend, etc . . .
    panels.append(Welcome())

    running = True
    while running:
        events = pygame.event.get()

        for p in panels:
            p.tick(surf, events, panels)

        pygame.display.flip()
        tps.tick()

        if len(panels) == 0:
            running = False;
        for e in events:
            if e.type == pygame.QUIT:
                running = False

        print(tps.spare_time_percent)

    pygame.font.quit()
    pygame.quit()
