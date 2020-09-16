#ifndef TEXT_H
#define TEXT_H

#include <cstdint>

namespace text {
  std::string reverse(std::string str) {
    std::string out = "";

    for(size_t i = 0; i < str.length(); i++) {
      out += str[str.length()-i-1];
    }
    return out;
  }

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

  uint8_t hex_to_uint8(std::string str) {
    assert(str.length() == 2);
    return (uint8_t)(hex_to_uint(str[0])*16 + hex_to_uint(str[1]));
  }

  std::string u8_to_hex(uint8_t n) {
    std::string out = "";
    for(int i = 0; i < 2; i++) {
        uint8_t nib = n%16;
        n /= 16;

        if(nib < 10) out += nib+'0';
        else out += (nib-10)+'a';
    }
    return reverse(out);
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

  std::string u16_to_hex(uint16_t n) {
    std::string out = "";
    for(int i = 0; i < 4; i++) {
        uint8_t nib = n%16;
        n /= 16;

        if(nib < 10) out += nib+'0';
        else out += (nib-10)+'a';
    }
    return reverse(out);
  }


  // removes space and #comments
  std::string clean_str(std::string line) {
    std::string not_ignored = "";

    bool is_comment = false;
    for(int i = 0; i < line.length(); i++) {
      char c = line[i];

      if(c == ' ') continue;
      else if(c == '#') is_comment = true;
      else if(!is_comment) not_ignored += c;
    }
    return not_ignored;
  }
}

#endif
