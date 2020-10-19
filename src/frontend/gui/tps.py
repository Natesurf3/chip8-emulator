import pygame

# better than pygame.Clock
# ticks are delayed to floating point accuracy on average(millisecond precision)
# also provides spare_time_percent
class Tps:
    def __init__(self, tps):
        self.last_tick = pygame.time.get_ticks()
        self.tick_len = 1000/tps
        self.spare_time_percent = 0

    def tick(self):
        dt = pygame.time.get_ticks()-self.last_tick
        st = self.tick_len - dt
        
        if st <= 0:
            sleep = 0
            self.last_tick += self.tick_len
        else:
            sleep = int(st)
            self.last_tick += self.tick_len*2-int(self.tick_len)

        self.spare_time_percent *= 0.95
        self.spare_time_percent += 0.05*st/self.tick_len

        pygame.time.delay(sleep)
