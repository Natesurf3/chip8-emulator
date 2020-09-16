## Assembler Statements

#### Syntax
lines which contain only hexadecimal characters are ignored
otherwise expects space delimited, one statement per line: "opname x y z"  
1 to 1 relationship from opname to opcode  
x y and z are required insofar as they are listed here. This compiles directly down to the hex string on the left no intermediate steps.  
variables are always hex numbers _only_, and are automatically zero padded (5 -> 005).  
Example: "jump 5" -> (4, "5") -> ("1xxx", "005")-> "1005"  
-----------------------------------------------------------------------
 3: 00EE : return  
 5: 2xxx : call x  
 4: 1xxx : jump x  
22: Bxxx : jumppv x  

 6: 3xyy : ==v x y  
 7: 4xyy : !==v x y  
 8: 5xy0 : == x y  
20: 9xy0 : !== x y  
25: Ex9E : ==press x  
26: ExA1 : !==press x  
28: Fx0A : waitkey x  

 9: 6xyy : setv x y  
11: 8xy0 : set x y  

10: 7xyy : +v x y  
15: 8xy4 : + x y  
16: 8xy5 : - x y  
18: 8xy7 : -- x y  

23: Cxyy : randv x y  
12: 8xy1 : | x y  
13: 8xy2 : & x y  
14: 8xy3 : ^ x y  
17: 8xy6 : >> x y  
19: 8xyE : << x y  

27: Fx07 : getD x  
29: Fx15 : setD x  
30: Fx18 : setS x  

21: Axxx : setIv x  
31: Fx1E : setIp x  
32: Fx29 : setIFont x  

34: Fx55 : memset x  
35: Fx65 : memget x  
33: Fx33 : digits x  
24: Dxyz : render x y z  
 2: 00E0 : cls  
-----------------------------------------------------------------------
