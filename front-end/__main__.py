import pygame

from panels.welcome import Welcome

win_init_size = (1024, 512)
if __name__ == "__main__":
    pygame.init()
    pygame.font.init()

    surf = pygame.display.set_mode(win_init_size, pygame.RESIZABLE)
    clock = pygame.time.Clock()

    panels = []     # filter, clear, extend, etc . . .
    panels.append(Welcome())

    running = True
    while running:
        events = pygame.event.get()

        for p in panels:
            p.tick(surf, events, panels)

        pygame.display.flip()
        clock.tick(60)

        if len(panels) == 0:
            running = False;
        for e in events:
            if e.type == pygame.QUIT:
                running = False

    pygame.font.quit()
    pygame.quit()
