import socket

# sending numbers: always little endian

chunk_size = 1024
class MessageSocket:
    def __init__(self, type, ip, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.type = type
        self.ip = ip
        self.port = port

    def open(self):
        if self.type == 'client':
            self.sock.connect((self.ip, self.port))
        elif self.type == 'server':
            self.sock.bind((self.ip, self.port))
            self.sock.listen(1)
            (newsock, addr) = self.sock.accept()
            self.sock = newsock

    def send(self, msg):
        self.__send_raw(len(msg).to_bytes(4, byteorder='little'))
        self.__send_raw(bytes(msg, encoding="ascii"))

    def recv(self):
        msg_len = int.from_bytes(self.__recv_raw(4), byteorder='little')
        msg = self.__recv_raw(msg_len).decode("ascii")
        return msg

    def close(self):
        self.sock.close()

# --- private ---
    def __send_raw(self, msg):
        amt_total = len(msg)
        amt_sent = 0

        while amt_sent < amt_total:
            amt = self.sock.send(msg[amt_sent:])
            amt_sent += amt
            if amt == 0:
                raise RuntimeError("connection broken")

    def __recv_raw(self, amt_total):
        amt_recvd = 0
        chunks = []

        while amt_recvd < amt_total:
            chunk = self.sock.recv(min(amt_total-amt_recvd, chunk_size))
            chunks.append(chunk)
            amt_recvd += len(chunk)
            if chunk == b'':
                raise RuntimeError("connection broken")

        return b''.join(chunks)
