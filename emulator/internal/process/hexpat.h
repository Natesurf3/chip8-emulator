#ifndef DECODER_H
#define DECODER_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <cassert>
#include <vector>
#include <string>

namespace hexpat {
  bool is_hex_digit(char c) {
    return (c >= '0' && c <= '9') ||
        (c >= 'A' && c <= 'F');
  }
  unsigned int hex_to_uint(char c) {
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
  unsigned int arg_to_uint(char c) {
    if(is_arg_digit(c))
      return c-'x';
    else
      assert(false);
  }

  std::string u16_to_binary(uint16_t n) {
    std::string out = "";
    for(int i = 0; i < 16; i++) {
        char digit = ('0'+n%2);
        n = n/2;
        out = digit + out;
    }
    return out;
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
    std::string str_rep;

  public:
    Pattern(std::string str_rep, int opcode) {
      this->str_rep = str_rep;
      this->opcode = opcode;

      assert(str_rep.length() == 4);


      for(int i = 0; i < 4; i++) {
        char ch = str_rep[3-i];

        if(is_hex_digit(ch)) {
          // exact binary match required for hex bits
          eq_bits |= (hex_to_uint(ch) << i*4);
        }
        else if(is_arg_digit(ch)){
          or_bits |= (0xF << i*4); // variable (argument) bits
          eq_bits |= (0xF << i*4); // are set to 1, making them ignorable

          // store location of variable bits in array
          // so they can be extracted into argument list
          int argn = arg_to_uint(ch);
          arg_bits[argn] |= (0xF<<i*4);
          if(!arg_exists[argn]) {
            arg_exists[argn] = true;
            arg_sh[argn] = i*4;
          }
        }
      }

      std::cout << u16_to_binary(or_bits) << std::endl;
      std::cout << u16_to_binary(eq_bits) << std::endl;
    }

    /*
      int ret[4] = [opcode, arg1, arg2, arg3]
    */
    bool try_match(int *ret, uint16_t instr) {
      bool is_match = (instr|or_bits) == eq_bits;

      if(is_match) {
        ret[0] = opcode;
        for(int i = 0; i < 3; i++) {
            ret[i+1] = ((instr&arg_bits[i]) >> arg_sh[i]);
        }
      }

      return is_match;
    }
  };


  class InstructionSet {
    std::vector<Pattern> patterns;

  public:
    InstructionSet() {
      load_from_file("./process/chip8.hpt");
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
    void load_from_file(std::string fname) {
      std::ifstream f(fname);
      std::string line;

      int op = -999; //TODO: debug
      while(std::getline(f, line)) {
        std::string not_ignored = "";

        bool is_comment = false;
        for(int i = 0; i < line.length(); i++) {
          char c = line[i];

          if(c == ' ')
            continue;
          else if(c == '#')
            is_comment = true;
          else if(!is_comment)
            not_ignored += c;
        }

        std::cout << op << " " << not_ignored << std::endl;
        if(not_ignored == "")
          continue;
        else if(not_ignored.find("setop") == 0)
          op = std::stoi(not_ignored.substr(5, std::string::npos));
        else if(not_ignored.find("skip") == 0)
          op++;
        else if(not_ignored.length() == 4){
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