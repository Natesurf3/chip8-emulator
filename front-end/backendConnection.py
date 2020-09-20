import zmq
import json

class Chip8EngineConnection:
	def receiveGraphics(switch):
		pass

	def sendRequest(keypresses):
		pass

	def getReply():
		pass

	def sendKeyPresses():
		pass

	def connect():
		pass

	def close():
		pass




class Chip8EngineCEngineConnection(Chip8EngineConnection):
	def __init__(self):
		context = zmq.Context()
		self.sock = context.socket(zmq.REQ)
		self.sock.bind("tcp://*:3000")


	def sendKeyPresses(self, keypresses):
		self.sock.send(keypresses)
		self.sock.recv()

	def sendRequest(self, keypresses):
		self.sock.send_string(json.dumps({'requestType': 'all', 'keys': keypresses}))

	def getReply(self):
		return json.loads(self.sock.recv())

	def receiveGraphics(self):
		numPixels = SCREEN_WIDTH * SCREEN_HEIGHT
		return [True] * numPixels
		# self.sock.send("graphics")
		# pixels = self.sock.recv()
		# self.pixel_setter(pixels)


	def connect(self):
		self.sock.bind("tcp://*:5555")

	def close():
		self.sock.close()
