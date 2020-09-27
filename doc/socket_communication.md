# How to communicate between processes

This is just a document to put ideas about communication so that we can keep track across files  
Nothing is set in stone, so if there's any other stuff please add  

### high level ideas
backend needs to send:  
 * graphics  
 * sound  
 * error messages

frontend needs to send:  
 * start message + config
 * stop message

 * key-state  
 * new settings  

communication is in a request-reply format to keep time
frontend sends data (request), then backend sends data (response).


### actual structure
-- backend reply --
{
  content: ["frame"]
  frame: {
    is_error: bool
    graphics: bool array[32*64]
    sound: bool
  }
}
-- frontend --
{
  content: ["frame", "state", "config"]
  frame: {
    keystate: bool array[16]
  }
  state: "start" or "stop" or "pause"
  config: complicated object
}

this way i think it will be easier to keep track of stuff if all the data arrives
combined in a single object each frame, instead of a multiple requests happening
asychronously

instead of having different message types, every message is the same format,
and any item omitted has to be omitted from the content list.  
However, for example, backend may assert("frame" in content) for every message
after state: "start" until state: "stop"
