# Disclaimer:
# This File is a WORK IN PROGRESS
# Also the markdown does not render properly. View it in a text editor.

# Instruction Set

### unsupported
 1: 0nnn
### control
#### functions
 3: 00EE -- return
 5: 2xxx -- call subroutine at x

#### jump
 4: 1xxx -- jump to x
22: Bxxx -- jump to x+r[0]

#### conditional
##### logic
 6: 3xyy -- skip if r[x] == y
 7: 4xyy -- skip if r[x] != y
 8: 5xy0 -- skip if r[x] == r[y]
20: 9xy0 -- skip if r[x] != r[y]
##### keys
25: Ex9E -- skip if keys[r[x]] == pressed
26: ExA1 -- skip if keys[r[x]] != pressed
28: Fx0A -- wait for key press, r[x] = key_id

#### Primary registers (r[x])
##### set
 9: 6xyy -- set r[x] = y
11: 8xy0 -- set r[x] = r[y]

##### rand
23: Cxyy -- set r[x] = y & rand

##### logic
12: 8xy1 -- set r[x] = r[x]|r[y]
13: 8xy2 -- set r[x] = r[x]&r[y]
14: 8xy3 -- set r[x] = r[x]^r[y]

##### add
10: 7xyy -- set r[x] = r[x]+y, no flag change
15: 8xy4 -- set r[x] = r[x]+r[y], set r[F] = is_overflow

##### sub
16: 8xy5 -- set r[x] = r[x]-r[y]
18: 8xy7 -- set r[x] = r[y]-r[x]
 * 16/18: r[F] = 0 when there's a borrow else 1. need definition for detecting 'a borrow'

##### shift
17: 8xy6 -- shift right = /2 = >>;  r[F] = lost_bit;
19: 8xyE -- shift left = *2 = <<;  r[F] = lost_bit;
 * differences
    * chip8 = shift y and store in x
    * schip and chip-48 = shift x and store in x; ignore y
##### timer
27: Fx07 -- r[x] = r.dt
29: Fx15 -- r.dt = r[x]
30: Fx18 -- r.st = r[x]


#### Ram
##### index pointer
21: Axxx -- set r.i = x
31: Fx1E -- r.i = r.i+r[x]
32: Fx29 -- r.i = default_font.sprite_address[x]

##### copy registers
34: Fx55 -- ram[r.i:r.i+x] = r[0:x]
35: Fx65 -- r[0:x] = ram[r.i:r.i+x]
 * differences
    * chip8 and chip-48 = r.i += x (x-1? x+1?)
    * schip = r.i is unmodified

##### generate digits (BCD)
33: Fx33 -- ram[r.i:r.i+3] = digits(r[x])

##### display
24: Dxyz -- render ram[r.i:r.i+z] at (r[x], r[y]); r[F] = 1 if any pixel changes from 1 to 0 else 0
 2: 00E0 -- clear screen, no flag change



----------------------------------------------------------------------
# Explanations:
## Terms
nibble = 4 bits = one hexadecimal digit
byte = 8 bits = unit of memory
pointer = 12 bits = allows 4k memory

stack pointer = is not a real pointer. it is the only pointer which is 4 bits long

| = bitwise or
& = bitwise and
^ = bitwise XOR

## Registers = r = additional memory
r[0] - r[F] = 16 primary byte registers
r[F] is used for flags like overflow, borrow, etc
r.i = 12 bit index pointer (for accessing ram)

## Control
### Program counter
typical program counter; r.pc increments each tick
r.pc = program counter = pointer
jump to x: r.pc = x
skip: r.pc += 1,

### Stack
r.st = stack pointer = nibble
r.st points to one of 16 pointers on r.stack which point to code locations in ram
stack is only used in subroutine and return

##### subroutine at x:
>r.stack[r.st] = r.pc # save current location
r.st += 1 # move up the stack
r.pc = x # jump to subroutine

##### return:
>r.st -= 1 # move down stack
r.pc = r.stack[r.st] # recall previous location

a program could theoretically call subroutine 16 times in a row. after that behavior is undefined
