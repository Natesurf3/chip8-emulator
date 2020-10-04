def key_line(line):
    loc = line.find(':')
    if loc < 3 and loc >= 0:
        return int(line[0:loc].strip())
    else:
        return 999999


def convert(f1, f2):
    f_in = open(f1, "rt")
    f_out = open(f2, "wt")
    lines = f_in.readlines()

    lines.sort(key=key_line)
    f_out.writelines(lines)

    f_out.close()
    f_in.close()

def convert_interactive():
    print(">> file1 = ", end="")
    f1 = input()

    print(">> file2 = ", end="")
    f2 = input()

    convert(f1, f2)
    print("Done")


if __name__ == "__main__":
    if 0: convert_interactive()
    else: convert("../../doc/research.md", "../../doc/research_sorted.md")
