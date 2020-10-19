#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include <iostream>
#include <cassert>
#include "../../../lib/rapidjson/document.h"
#include "../../../lib/rapidjson/stringbuffer.h"
#include "../../../lib/rapidjson/writer.h"

#include "message_types.h"
using namespace rapidjson;

// ---- converting json string <--> data types
InMessage load_message(std::string message) {
  InMessage msg;
  Document doc;
  doc.Parse(message.c_str());
  assert(doc.IsObject());

  if(msg.is_frame = doc.HasMember("frame")) {
    assert(doc["frame"].IsObject());
    assert(doc["frame"].HasMember("keystate"));
    assert(doc["frame"]["keystate"].IsArray());
    assert(doc["frame"]["keystate"].Size() == 16);

    const Value& keystate = doc["frame"]["keystate"];
    for(SizeType i = 0; i < keystate.Size(); i++) {
      assert(keystate[i].IsBool());
      msg.keystate[i] = keystate[i].GetBool();
    }
  }

  if(msg.is_state = doc.HasMember("state")) {
    assert(doc["state"].IsString());
    msg.state = doc["state"].GetString();

    if(msg.state == "start") {
      assert(doc.HasMember("start_path"));
      assert(doc["start_path"].IsString());
      msg.start_path = doc["start_path"].GetString();
    }
  }

  if(msg.is_config = doc.HasMember("config")) {
    assert(doc["config"].IsObject());
    //assert(false); //TODO: implement
  }

  return msg;
}

std::string dump_message(OutMessage msg) {
  Document doc;
  doc.SetObject();
  Document::AllocatorType& alloc = doc.GetAllocator();
  doc.AddMember("content", Value(kArrayType), alloc);

  if(msg.is_frame) {
    doc["content"].PushBack("frame", alloc);

    Value graph(kArrayType);
    for(size_t i = 0; i < 32*64; i++)
      graph.PushBack(msg.graphics[i], alloc);

    Value frame(kObjectType);
    frame.AddMember("is_error", msg.is_error, alloc);
    frame.AddMember("sound", msg.sound, alloc);
    frame.AddMember("graphics", graph, alloc);
    doc.AddMember("frame", frame, alloc);
  }

  StringBuffer buff;
  Writer<StringBuffer, Document::EncodingType, ASCII<>> writer(buff);
  doc.Accept(writer);
  return buff.GetString();
}
#endif
