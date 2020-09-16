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


def remove_ignored(st):
    (st1, _) = grab(st, "/*", "*/")        # multiline comments #
    (st2, _) = grab(st1, "#", "\n", "\n")  # single line comments #
    (st3, _) = grab(st2, " ")              # spaces #


    st4 = st3[:] # empty lines #
    while "\n\n" in st4:
        (st4, _) = grab(st4, "\n\n", "", "\n")

    return st4



def compile(ifname, ofname):
    inf = open(ifname, "rt")
    st = inf.read()
    inf.close()
    # ---- compilation ----]

    # comments and empty lines
    st1 = remove_ignored(st)

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

    print(st4)

    # ---- end compilation ----
    ouf = open(ofname, "wt")
    ouf.write(st4)
    ouf.close()

    logs = [st1, st2, st3]
    for i in range(0,3):
        f = open("../resources/log_"+str(i), "wt")
        f.write(logs[i])
        f.close()


if __name__ == "__main__":
    if True:
        compile("../resources/test_rom.cha",
                "../resources/test_rom.txt")
    else:
        print(">> Welcome to HEXP COMPILE")
        print(">> ifname: ", end="")
        ifname = input()
        print(">> ofname: ", end="")
        ofname = input()

        compile(ifname, ofname)
        print(">> DONE")
