import zmq
import json

# abstracting out sockets
class Communicator():
    def __init__(self):
        context = zmq.Context()
        self.sock = context.socket(zmq.REP)

    def bind(self):
        print("listening on port 3000")
        self.sock.bind("tcp://127.0.0.1:3000")

    def send(self, data):
        self.sock.send_string(json.dumps(data))

    def recv(self):
        return json.loads(self.sock.recv())

    def close():
        self.sock.close()

t = 0
def create_response(req):
    global t
    t += 32*64
    if 'frame' in req['content']:
        return {
            'content': ["frame"],
            'frame': {
                'graphics': list(map(
                    lambda ix: round( (ix+t/100) / 10)%2,
                    range(32*64)
                )),
                'sound': True
            }
        }
    else:
        print(str(req))
        print("content.frame is None")
        # console.log(`Request: ${JSON.stringify(req)}`)
        # console.log(response_str)


if __name__ == '__main__':
    com = Communicator()
    com.bind()
    while True:
        com.send(create_response(com.recv()))
