# ------------------------------------------------------
# formatting chip8 binary ROM in hexadecimal and ASCII
# ------------------------------------------------------

# bins = binary format
# ascii = text format

hex = [
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F',
]

# ------------------------------------------------------
# ----------------| BINARY --> ASCII |------------------
# ------------------------------------------------------
def bin_to_ascii(bin):
    a = bin//16;
    b = bin%16;
    return hex[a]+hex[b]

# formats to hex string with 4 nibbles per line
def bins_to_ascii(bins):
    out = ""
    for i in range(0, len(bins)):
        out += bin_to_ascii(bins[i])
        if i%2 == 1:
            out += "\n"

    return out

# ------------------------------------------------------
# ----------------| ASCII --> BINARY |------------------
# ------------------------------------------------------
def ascii_to_bin(ascii):
    assert(ascii[0] in hex and ascii[1] in hex)
    a = hex.index(ascii[0])
    b = hex.index(ascii[1])
    return a*16 + b

def ascii_to_bins(ascii):
    out = []

    ascii = ascii.replace("\n", "")
    for i in range(0, len(ascii)-1, 2):
        out.append(ascii_to_bin(ascii[i:i+2]))

    if len(ascii)%2 != 0:
        print("*************** half-byte error *********************")

    return out

# ------------------------------------------------------
# --------------------| FILE IO |-----------------------
# ------------------------------------------------------
def read_bins(filename):
    file = open(filename, "rb")
    bins = []
    while True:
        bin_arr = file.read(1)
        if len(bin_arr) == 0:
            break;
        bins.append(bin_arr[0])
    file.close()
    return bins

def read_ascii(filename):
    file = open(filename, "rt")
    str = file.read()
    file.close()
    return str

def write_ascii(filename, ascii):
    file = open(filename, "wt")
    file.write(ascii)
    file.close()

def write_bins(filename, bins):
    file = open(filename, "wb")
    file.write(bytes(bins))
    file.close()
# ------------------------------------------------------
# ---------------------| TEST |-------------------------
# ------------------------------------------------------

import os
# converts to ascii and back.
# contents of ./test/<fname>_2 should equal contents of fname
# on linux use 'diff' command to verify
def test_convert(fname):
    if not os.path.exists("./temp"):
        os.makedirs("./temp")

    fname_1 = "./temp/"+fname+"_1"
    fname_2 = "./temp/"+fname+"_2"

    bins = read_bins(fname)
    write_ascii(fname_1, (bins_to_ascii(bins)))

    ascii = read_ascii(fname_1)
    write_bins(fname_2, ascii_to_bins(ascii))

    print("-----------bins0-----------")
    print(bins)
    print("-----------ascii----------")
    print(ascii)

# ------------------------------------------------------
# ---------------------| MAIN |-------------------------
# ------------------------------------------------------
if __name__ == "__main__":
    print(">> Welcome to hex-ascii repl")

    while True:
        print(">> Press enter to continue or type 'quit' to exit: ", end="")
        cmnd = input()
        if cmnd == "quit":
            break;

        print(">> ifname: ", end="")
        ifname = input()

        print(">> valid iftypes are ['ascii', 'bins']: ", end="")
        iftype = input()

        print(">> ofname: ", end="")
        ofname = input()

        if iftype == "bins":
            bins = read_bins(ifname)
            write_ascii(ofname, bins_to_ascii(bins))
        elif iftype == "ascii":
            ascii = read_ascii(ifname)
            write_bins(ofname, ascii_to_bins(ascii))
        else:
            print(">> invalid iftype")
