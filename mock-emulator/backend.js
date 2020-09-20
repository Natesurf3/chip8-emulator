const zmq = require("zeromq")

async function run() {
  const sock = new zmq.Reply

  sock.connect("tcp://127.0.0.1:3000")
  console.log("Backend connected to port 3000")

  for await (const [msg] of sock) {
    await sock.send(createResponse(msg))
  }
}

const createGraphicsResponse = () => {
	let arr = Array(64 * 32).fill(false)
	for (var i = 0; i < arr.length; i += 2) {
		arr[i] = true
	}
	return arr
}
const createResponse = request => {
	console.log(`Request: ${JSON.stringify(JSON.parse(request.toString()))}`)
	let req = JSON.parse(request.toString())
	let response = {requestType: req.requestType}

	switch (req.requestType) {
		case "all": {
			response.payload = {
				graphics: createGraphicsResponse(),
				sound: true
			}
			break
		}
		case "graphics": {
			response.payload = Array(64 * 32).fill(false)
			for (var i = 0; i += 2; i < 64*32) {
				response.payload[i] = true
			}
			break
		}
		case "sound": {
			response.payload = false
			break
		}
		case "keypresses": {
			break
		}
		default: Error("Unable to interpret request!")
	}
	console.log(response)
	return JSON.stringify(response)
}
run()