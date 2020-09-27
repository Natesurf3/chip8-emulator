import zmq
import json

# abstracting out sockets
class Communicator():
	def __init__(self):
		context = zmq.Context()
		self.sock = context.socket(zmq.REQ)

	def connect(self):
		self.sock.bind("tcp://*:3000")

	def send(self, data):
		self.sock.send_string(json.dumps(data))

	def recv(self):
		return json.loads(self.sock.recv())

	def close():
		self.sock.close()
