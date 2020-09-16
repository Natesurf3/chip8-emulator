# ------------------------------------------------------
# formatting chip8 binary ROM in binary and hex
# ------------------------------------------------------

# bins = binary raw format
# hex = hexadecimal text format

hex_ch = [
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F',
]

# ------------------------------------------------------
# ----------------| BIN --> HEX |------------------
# ------------------------------------------------------
def bin_to_hex(bin):
    a = bin//16;
    b = bin%16;
    return hex_ch[a]+hex_ch[b]

# formats to hex string with 4 nibbles per line
def bins_to_hexs(bins):
    out = ""
    for i in range(0, len(bins)):
        out += bin_to_hex(bins[i])
        if i%2 == 1:
            out += "\n"

    if len(bins)%2 == 0:
        out += "00\n" # padding

    return out

# ------------------------------------------------------
# ----------------| HEX --> BIN |------------------
# ------------------------------------------------------
def hex_to_bin(hex):
    assert(hex[0] in hex_ch and hex[1] in hex_ch)
    a = hex_ch.index(hex[0])
    b = hex_ch.index(hex[1])
    return a*16 + b

def hexs_to_bins(hex):
    out = []

    hex = hex.replace("\n", "")
    for i in range(0, len(hex)-1, 2):
        out.append(hex_to_bin(hex[i:i+2]))

    if len(hex)%2 != 0:
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

def read_hexs(filename):
    file = open(filename, "rt")
    str = file.read()
    file.close()
    return str

def write_hexs(filename, hex):
    file = open(filename, "wt")
    file.write(hex)
    file.close()

def write_bins(filename, bins):
    file = open(filename, "wb")
    file.write(bytes(bins))
    file.close()
# ------------------------------------------------------
# ---------------------| TEST |-------------------------
# ------------------------------------------------------

import os
# converts to hex and back.
# contents of ./test/<fname>_2 should equal contents of fname
# on linux use 'diff' command to verify
def test_convert(fname):
    if not os.path.exists("./temp"):
        os.makedirs("./temp")

    fname_1 = "./temp/"+fname+"_1"
    fname_2 = "./temp/"+fname+"_2"

    bins = read_bins(fname)
    write_hexs(fname_1, (bins_to_hexs(bins)))

    hex = read_hexs(fname_1)
    write_bins(fname_2, hexs_to_bins(hex))

    print("-----------bins0-----------")
    print(bins)
    print("-----------hex----------")
    print(hex)

# ------------------------------------------------------
# ---------------------| MAIN |-------------------------
# ------------------------------------------------------
if __name__ == "__main__":
    print(">> Welcome to hex-hex repl")

    while True:
        print(">> Press enter to continue or type 'quit' to exit: ", end="")
        cmnd = input()
        if cmnd == "quit":
            break;

        print(">> ifname: ", end="")
        ifname = input()

        print(">> valid iftypes are ['hex', 'bins']: ", end="")
        iftype = input()

        print(">> ofname: ", end="")
        ofname = input()

        if iftype == "bins":
            bins = read_bins(ifname)
            write_hexs(ofname, bins_to_hexs(bins))
        elif iftype == "hex":
            hex = read_hexs(ifname)
            write_bins(ofname, hexs_to_bins(hex))
        else:
            print(">> invalid iftype")
