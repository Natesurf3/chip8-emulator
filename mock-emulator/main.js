const zmq = require("zeromq")


function range_list(a, b) {
  l = []
  for(let i = a; i < b; i++) {
    l.append()
  }
}

async function run() {
  const sock = new zmq.Reply

  sock.connect("tcp://127.0.0.1:3000")
  console.log("Backend connected to port 3000")

  for await (const [msg] of sock) {
    await sock.send(createResponse(msg))
  }
}
let t = 0
const createResponse = request => {
  let req = JSON.parse(request.toString())
  if(req.content.includes("frame")) {
    return JSON.stringify({
      content: ["frame"],
      frame: {
        graphics: Array.from(Array(32*64)).map(
            (val, ix) => Math.round((ix+(++t)/100)/10)%2),
        sound: true
      }
    })
  } else {
    console.log(request.toString())
    console.log("content.frame is undefined")
  }
  //  console.log(`Request: ${JSON.stringify(req)}`)
  //  console.log(response_str)
}
run()
