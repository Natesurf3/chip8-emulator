#ifndef MESSAGE_SOCKET_H
#define MESSAGE_SOCKET_H

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <algorithm>
#include <cstdint>
#include <string>
#include <iostream>
#include <cassert>

typedef struct sockaddr_in AddrInet; // ipv4
typedef struct sockaddr Addr; // generic

const auto sock_close = close;

class MessageSocket {
  int sock;
  int sock_cn;
  int buff_size = 1024;

  int type;
  std::string ip;// = "127.0.0.1";
  int port;// = 8080;

public:
  static const int server = 1;
  static const int client = 2;

  MessageSocket(int type_, std::string ip_, int port_) {
    type = type_;
    ip = ip_;
    port = port_;

    // Create tcp socket over ipv4 (SOCK_STREAM socket over AF_INET)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    assert(sock != -1);
  }

  void open() {
    if(type == server) {
      // set option to to allow for other sockets to use the same port or addr
      // those sockets will be ignored and at least wont make the program crash
      int opt = 1;
      int opt_status = setsockopt(sock, SOL_SOCKET,
          SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
      assert(opt_status == 0);

      // bind to address
      AddrInet address;
      address.sin_family = AF_INET;
      address.sin_addr.s_addr = INADDR_ANY;
      address.sin_port = htons(port);
      int bind_status = bind(sock, (Addr*)&address, sizeof(address));
      assert(bind_status == 0);

      // how to listen
      int listen_status = listen(sock, 1);
      assert(listen_status == 0);

      // wait and accept next connection
      Addr client_addr;
      socklen_t client_addr_size;
      sock_cn = accept(sock, &client_addr, &client_addr_size);
      assert(sock_cn != -1);
    }
    else if(type == client) {
      // set address
      AddrInet address;
      address.sin_family = AF_INET;
      address.sin_port = htons(port);
      int addr_status = inet_pton(address.sin_family, ip.c_str(), &address.sin_addr);
      assert(addr_status == 1);

      // connect to existing server
      int connect_status = connect(sock, (Addr *)&address, sizeof(address));
      assert(connect_status >= 0);
      sock_cn = sock;
    }
    else {
      assert(false);
    }
  }

  void send(std::string msg) {
    uint32_t len = msg.length();
    char *header = (char *)&len; // TODO: only works for x86 systems
    send_raw(header, 4);
    send_raw(msg.c_str(), len);
  }

  std::string recv() {
    std::string header = recv_raw(4);
    uint32_t *len = (uint32_t *)header.c_str();
    std::string msg = recv_raw(*len);
    return msg;
  }

  void close() {
    sock_close(sock);
  }

private:
  std::string recv_raw(size_t amt_total) {
    std::string msg = "";
    size_t amt_recvd = 0;

    while(amt_recvd < amt_total) {
      char buffer[buff_size] = {0};
      int amt = read(sock_cn, buffer, std::min(buff_size, (int)(amt_total-amt_recvd)));
      assert(amt > 0);

      std::string addition = std::string(buffer, amt);
      msg += addition;
      amt_recvd += amt;
    }
    return msg;
  }

  void send_raw(const char *data, size_t amt_total) {
    size_t amt_sent = 0;
    while(amt_sent < amt_total) {
      int amt = write(sock_cn, data+amt_sent, std::min(buff_size, (int)(amt_total-amt_sent)));
      amt_sent += amt;
      assert(amt != -1);
    }
  }
};
#endif
