import pygame

def convert_to_pxbound(bound, surf):
    return (round(bound[0]*surf.get_width()), round(bound[1]*surf.get_height()),
            round(bound[2]*surf.get_width()), round(bound[3]*surf.get_height()))

def convert_to_rlpos(pos, surf):
    return (pos[0]/surf.get_width(), pos[1]/surf.get_height())
