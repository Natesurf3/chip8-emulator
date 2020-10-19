#ifndef COMMUNICATOR_H
#define COMMUNICATOR_H

#include "message_socket.h"
#include "json_util.h"
#include "message_types.h"
#include "../util/logger.h"

class Communicator {
  MessageSocket sock = MessageSocket(MessageSocket::server, "127.0.0.1", 8080);

public:
  Communicator() {
    sock.open();
  }

  InMessage recv() {
    return load_message(sock.recv());
  }

  void send(OutMessage msg) {
    sock.send(dump_message(msg));
  }

  void close() {
    sock.close();
  }

};
#endif
