#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <string>

namespace instruction_set {
  bool is_hex_digit(char c) {
    return (ch >= '0' && ch <= '9') ||
        (ch >= 'A' && ch <= 'F');
  }
  unsized int hex_to_uint(char c) {
    if(c >= '0' && c <= '9')
      return c-'0';
    else if(c >= 'A' && c <= 'F')
      return c-'A' + 10;
    else
      assert(false);
  }

  bool is_arg_digit(char c) {
    return c >= 'x' && c <= 'z';
  }
  unsized int arg_to_uint(char c) {
    if(is_arg_digit)
      return c-'x';
    else
      assert(false);
  }


  /*
    binary pattern matching algorithm:
      0) receive a possible match
      1) use or_bits to overwrite variable bits with 1 so they are ignored
      2) eq_bits = hexadecimal pattern with variable bits also set to 1
      3) make sure result of part 1 == result of part 2
  */
  class Pattern {
    uint16_t or_bits = 0x0000;
    uint16_t eq_bits = 0x0000;

    bool arg_exists[3] = {false, false, false};
    uint16_t arg_bits[3] = {0x0000, 0x0000, 0x0000};
    int arg_sh[3] = {0,0,0};

    int opcode;
    string str_rep;

  public:
    Pattern(std::string str_rep, int opcode) {
      this.str_rep = str_rep;
      this.opcode = opcode;

      assert(str_rep.length == 4);


      for(int i = 0; i < 4; i++) {
        char ch = str_rep[i];

        if(is_hex_digit(ch)) {
          // exact binary match required for hex bits
          eq_bits |= hex_to_uint(ch) << i*8;
        }
        else if(is_arg_digit(ch)){
          or_bits |= 0xF << i*8; // variable (argument) bits
          eq_bits |= 0xF << i*8; // are set to 1 (making them ignorable)

          // store location of variable bits in array
          // so they can be extracted into argument list
          argn = arg_to_uint(ch);
          arg_bits[argn] |= (0xF<<i*8);
          if(!arg_exists[argn]) {
            arg_sh[argn] = i*8;
            arg_exists[argn] = true;
          }
        }
      }
    }

    /*
      int ret[4] = [opcode, arg1, arg2, arg3]
    */
    bool try_match(int *ret, uint16_t instr) {
      bool is_match = (instr|or_bits) == xor_bits;

      if(is_match) {
        ret[0] = this.opcode;
        for(int i = 0; i < 3; i++) {
            ret[i+1] = ((instr&arg_bits[i]) >> arg_sh[i]);
        }
      }

      return is_match;
    }
  };


  class InstructionSet {
    vector<Pattern> patterns;

  public:
    Patternset() {
      load_from_file("./chip8.hpt")
    }

    bool try_match(int *ret, uint16_t instr) {
      for(int i = 0; i < patterns.size(); i++) {
        if(patterns[i].try_match(ret, instr)) {
          return true;
        }
      }
      return false;
    }


    /* parses hpt file format */
    void load_from_file(string fname) {
      ifstream f(fnames[i]);
      string line;

      int op = 1;
      while(std::getline(f, line)) {
        string not_ignored = "";

        bool is_comment = false;
        for(int i = 0; i < line.length; i++) {
          char c = line[i];

          if(c == ' ')
            continue;
          else if(c == '#')
            is_comment = true;
          else if(!is_comment)
            not_ignored += c;
        }

        if(not_ignored == "")
          continue;
        else if(not_ignored.find("setop") == 0)
          op = std::stoi(not_ignored.substr(5, string::npos));
        else if(not_ignored.find("skip") == 0)
          op++;
        else if(not_ignored.length == 4){
          patterns.push_back(Pattern(not_ignored, op));
          op++;
        }
        else {
          assert(false);
        }
      }
    }
  };
}

#endif
