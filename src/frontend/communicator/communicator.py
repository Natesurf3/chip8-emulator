import zmq
import json
from communicator.message_socket import MessageSocket
# abstracting out sockets

class CommunicatorZmq():
	def __init__(self):
		context = zmq.Context()
		self.sock = context.socket(zmq.REQ)

	def connect(self):
		self.sock.connect("tcp://127.0.0.1:3000")

	def send(self, data):
		self.sock.send_string(json.dumps(data))

	def recv(self):
		return json.loads(self.sock.recv())

	def close(self):
		self.sock.close()

class Communicator():
	def __init__(self):
		self.sock = MessageSocket('client', "127.0.0.1", 8080)

	def connect(self):
		self.sock.open()

	def send(self, data):
		self.sock.send(json.dumps(data))

	def recv(self):
		return json.loads(self.sock.recv())

	def close(self):
		self.sock.close()
