# allows for use of comments and variables in a rom
def get_line(st, loc):
    l = 0
    for i in range(min(len(st), loc)):
        if st[i] == "\n":
            l += 1
    return l


def insert(st, value, start, len):
    return st[:start] + value + st[start+len:]

# searches for st2 in st1 starting at ix
def find(st1, ix, st2):
    if st2 in st1[ix:]:
        return ix + st1[ix:].find(st2)
    else:
        return -1

def int_to_hex3(i):
    st = hex(i)[2:].upper()
    while len(st) < 3:
        st = "0"+st
    return st

# locates all occurrance = ocr = start<inner>stop in string
# (with <inner> matching any amount of text)
# args:
#   start/stop: identical character string matches, "" matches anything
# return: tuple(
#       string with occurrances replaced,
#       namedtuple('inner','start' of ocr, 'len' of ocr)
# )
from collections import namedtuple
Item = namedtuple('Item', ('inner', 'start', 'length'))
def grab(st, start, stop="", replace=""):
    # find + collect occurrances
    items = []
    ix = 0
    while True:
        a = find(st, ix, start)
        b = find(st, a+len(start), stop)

        if a <= 0 or b <= 0:
            break

        ix = b+len(stop)
        items.append(Item(
            st[a+len(start):b],
            a,
            ix-a
        ))

    # replace occurances
    st1 = ""
    ix = 0
    for i in range(0, len(items)):
        (_, start, length) = items[i]
        st1 += st[ix:start] + replace
        ix = start+length
    st1 += st[ix:]

    return (st1, items)

# 4 hex characters, variable parts are labeled x, y, z
vars = ("x", "y", "z")
class Pattern:
    def __init__(self, line):
        info = line.strip().split(" ")
        assert(len(info) == 3)
        (self.opcode, self.hexstr, self.op_asm) = info
        self.is_arg = [v in self.hexstr for v in vars]

    def is_match_asm(self, line):
        return line.split(" ")[0] == self.op_asm

    def asm_to_hex(self, line):
        assert(self.is_match_asm(line))
        hex = self.hexstr[::-1]
        parts = line.split(" ")
        print("hex: " + hex)
        print("line: "+line)
        print("parts: "+str(parts))
        for (arg_, param) in zip(parts[1:], vars):
            arg = arg_[::-1]

            for c in arg:
                hex = insert(hex, c, hex.find(param), 1)

            hex = hex.replace(param, "0")
        print(hex)
        return hex[::-1]

    def is_match_hex(self, line):
        assert(len(line) == len(self.hexstr))
        for (a, b) in zip(self.hexstr, line):
            if (a != b) and (not a in vars):
                return False
        return True

    def hex_to_asm(self, line):
        assert(self.is_match_hex(line))

        args = [0,0,0]

        for c1, c2 in zip(self.hexstr, line):
            if c1 in vars:
                args[vars.index(c1)] *= 16
                args[vars.index(c1)] += int(c2, 16)

        info = self.op_asm
        for i in range(len(args)):
            if self.is_arg[i]:
                info += " " + hex(args[i])[2:].upper()
        return info

def load_chip8_iset():
    iset = []
    f = open("./chip8.asp", "rt")
    for line in f.readlines():
        iset.append(Pattern(line.strip()))
    return iset


def compile_A(st):
    # remove lots of stuff
    (st1, _) = grab(st, "/*", "*/")        # multiline comments #
    (st1, _) = grab(st1, "#", "\n", "\n")  # single line comments #
    while " \n" in st1:
        (st1, _) = grab(st1, " \n", "", "\n")  # spaces at end of line #
    while "\n\n" in st1:                   # empty lines #
        (st1, _) = grab(st1, "\n\n", "", "\n")

    # grab user-variable definitions
    (st2, items) = grab(st1, "|", "|\n")

    # replace user-variable usages
    st3 = st2[:]
    for (i, (inner, start, length)) in enumerate(items):
        value = int_to_hex3(512+2*(get_line(st1, start)-i))
        pattern = "{"+inner+"}"
        (st3, _) = grab(st3, pattern, "", value)

    # replace assembler-variable usages
    st4 = st3[:]
    for starter in ["cm_", "cp_"]:
        for i in range(0, 5):
            pattern = "{"+starter+str(i)+"}"
            while pattern in st4:
                start = st4.find(pattern)
                value = int_to_hex3(512 + 2*get_line(st3, start))
                st4 = insert(st4, value, start, len(pattern))

    return (st1, st2, st3, st4)

# "jump 5" -> "1005"
def compile_B(st, iset):
    print(st)
    st1 = ""
    for line in st.split("\n"):
        for ins in iset:
            if ins.is_match_asm(line):
                st1 += ins.asm_to_hex(line)+"\n"
                break;
        else:
            st1 += line+"\n"

    return st1

import os
import bin_hex
def compile(fname, is_log=True):
    custom_rom = os.path.join(os.getcwd(), "../resources/custom_rom")
    ifname = os.path.join(custom_rom, "src", fname)
    ofname = os.path.join(custom_rom, "bin", os.path.splitext(fname)[0]+".ch8")
    logdir = os.path.join(custom_rom, "log", os.path.splitext(fname)[0])

    inf = open(ifname, "rt")
    st = inf.read()
    inf.close()

    (st1, st2, st3, st4) = compile_A(st)
    st5 = compile_B(st4, load_chip8_iset())

    if is_log:
        if not os.path.exists(logdir):
            os.makedirs(logdir)

        logs = [st1, st2, st3, st4, st5]
        for (i, st) in enumerate(logs):
            f = open(os.path.join(logdir, "log_"+str(i)), "wt")
            f.write(st)
            f.close()

    ouf = open(ofname, "wb")
    ouf.write(bytes(bin_hex.hexs_to_bins(st5)))
    ouf.close()


# decompiling any of part A will probably never happen
# however this is reasonable:
def decompile(fname, is_log=True):
    curated_rom = os.path.join(os.getcwd(), "../resources/curated_rom")
    decompiled_rom = os.path.join(os.getcwd(), "../resources/decompiled_rom")

    ifname = os.path.join(curated_rom, fname)
    ofname = os.path.join(decompiled_rom, "src", os.path.splitex(fname)[0]+".cha")
    logdir = os.path.join(decompiled_rom, "log", os.path.splitex(fname))

    inf = open(ifname, "rb")
    st = bin_hex.bins_to_hexs(inf.read())
    inf.close()

    # decompile part B
    iset = load_chip8_iset();
    st1 = ""
    for line in st.split():
        for ins in iset:
            if ins.is_match_hex(line):
                st1 += ins.hex_to_asm(line)+"\n"
                break;
        else:
            st1 += line+"\n"

    ouf = open(ofname, "wt")
    ouf.write(st1)
    ouf.close()

    if is_log:
        if not os.path.exists(logdir):
            os.makedirs(logdir)

        logs = [st]
        for (i, st) in enumerate(logs):
            f = open(os.path.join(logdir, "log_"+str(i)), "wt")
            f.write(st)
            f.close()



import prompt
if __name__ == "__main__":
    if True:
        compile("test_rom.cha", load_chip8_iset())
    else:
        print(">> Welcome to HEXP COMPILE")
        print(">> ifname: ", end="")
        ifname = input()
        print(">> ofname: ", end="")
        ofname = input()

        compile(ifname, ofname)
        print(">> DONE")
