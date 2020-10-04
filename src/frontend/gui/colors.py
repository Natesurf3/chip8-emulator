BLACK = (0,0,0)
WHITE = (255,255,255)

GREY_BLACK = (51,51,51)
GREY_DARK  = (89,89,89)
GREY       = (128,128,128)
GREY_LIGHT = (165,165,165)
GREY_WHITE = (204,204,204)

RED = (255,0,0)
GREEN = (0,255,0)
BLUE = (0,0,255)

YELLOW = (255,255,0)
TURQUOISE = (0,255,255)
PURPLE = (255,0,255)

def blend(c1, c2, amount=0.5):
    return (
        c1[0]*(1-amount) + c2[0]*amount,
        c1[1]*(1-amount) + c2[1]*amount,
        c1[2]*(1-amount) + c2[2]*amount
    )
