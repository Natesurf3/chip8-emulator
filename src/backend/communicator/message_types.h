#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H
#include <string>
#include <sstream>
/**
-- send from backend --
{
  content: ["frame"]
  frame: {
    is_error: bool
    graphics: bool array[32*64]
    sound: bool
  }
}
-- receive from frontend --
{
  content: ["frame", "state", "config"]
  frame: {
    keystate: bool array[16]
  }
  state: "start" or "stop" or "pause"
  config: complicated object
}
**/
//---------- data types --------
class InMessage {
public:
  //frame
  bool is_frame = false;
  bool keystate[16] = {};

  //state
  bool is_state = false;
  std::string state;
  std::string start_path;

  //config
  bool is_config = false;

  // MISC
  std::string to_string();


};

class OutMessage {
public:
  OutMessage() {}

  //frame
  bool is_frame = false;
  bool is_error;
  bool *graphics;
  bool sound;
  OutMessage &set_frame(bool is_error_, bool *graphics_, bool sound_) {
    is_frame = true;
    is_error = is_error_;
    graphics = graphics_;
    sound = sound_;
    return *this;
  }
};



std::string InMessage::to_string() {
  std::stringstream out;
  out << "{\n";
  out << "  (is_frame, is_state, is_config) = ";
  out << "(" << is_frame << ", " << is_state << ", " << is_config <<")\n";

  if(is_frame) {
    out << "  InFrame: [";
    for(size_t i = 0; i < 16; i++)
      out << keystate[i] << " ";
    out << "]\n";
  }
  out << "  state: " << state << "\n";
  out << "}" << std::endl;

  return out.str();
}

#endif
