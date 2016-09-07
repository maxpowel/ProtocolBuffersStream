#include <ProtocolBuffersStream.h>

// You need to install this library https://github.com/nanopb/nanopb
#include <pb_encode.h>
#include <pb_decode.h>
#include "proto/command.pb.h"

// Instead of serial you can use sdcard or anything that implements the stream
// interface
ProtocolBuffersStream messenger(&Serial);

void setup() {
  Serial.begin(115200);

}


void loop() {
  // Wait for a command to execute
  Command c = Command_init_zero;
  // The messenger object needs the object interface (Command_fields) that
  // contains the object structure and the instace you want to populate
  if(messenger.receive(Command_fields, &c)) {
    Response response = Response_init_zero;
      if(c.command == 1) {
        // Do some stuff
        /* ....... */
        response.success = true;
        response.someValue = 3.1416
      } if(c.command == 2) {
        // Do some stuff
        /* ....... */
        response.success = true;
        response.someValue = 6346
      } else {
        // Command not found
        response.success = false;
      }
      // Serialization step has the same signature, the class structure and
      // the object instance with the data
      messenger.send(Response_fields, &response);
  } else {
    // Error while receiving command, you could do something here
  }

}
