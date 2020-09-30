# chip8-emulator
emulator for chip8

# Conventions
Code will try to avoid raw hexadecimal


# Linux
### Dependencies
 * g++
 * make
### How to run
 * open a terminal inside chip8-emulator
 * cd emulator/internal
 * make run

## Windows is a work in progress

# Filesytem
doc: explain the code  

emulator/internal: provides a virtual machine for the chip8 system
  * data: all the virtual memory
  * process: all the virtual instruction sets, virtual processor
  * util: mostly string processing

emulator/external: acts as a window manager, a console interface, or any other way of reaching the user

emulator/tools/assembler.py: compiles .cha to .hex  
emulator/tools/bin-hex.py: converts .hex to .ch8 and back  
emulator/tools/order.py: sorts through documentation  

tests: javascript prototype

resources: This folder mostly holds ROM and ROM-related stuff

## file types:
.hpt: describes any instruction set  
.cha: chip8 assembly  
.hex: chip8 machine code as hexadecimal text **(ROM format)**  
.ch8: chip8 machine code raw  


# Legal
This project is licensed under the GNU General Public License
