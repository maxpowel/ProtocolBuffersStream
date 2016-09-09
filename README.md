Protocol Buffers Stream
=======================

This library makes easy to send and receive protocol buffers objects through an arduino stream.
Serialize and deserialize is a complex task and it gets harder when you have to do it in a very
limited hradware like Arduino.

Simple interface
----------------
My intention is just send and receive objects.

First create the messenger (the thing that encapsulates all the complexity)

```c
    ProtocolBuffersStream messenger(&Serial);
```

You only need a stream, in this case I used Serial but it is fully compatible with SD, ethernet and any stuff
that implements the Stream class (https://www.arduino.cc/en/Reference/Stream)

For this example is used this proto definition:

```proto
message Sensor {
  required int32 id = 1;
  required value float = 2;
}
```

Once you have defined your data model (in this case just a class that contains sensor data) you may want to send it.

```c
Sensor sensor = Sensor_init_zero;
sensor.id = 0xabc
sensor.value = 56.43

bool success = messenger.send(Sensor_fields, &sensor);
```

Thats all, everything is serialized and sent. You also know if everything went fine.


Receiving objects is pretty easy too:

```c
Sensor sensor = Sensor_init_zero;

bool success = messenger.read(Sensor_fields, &sensor);
if (success) {
   sensor.id = 0xabc
   sensor.value = 56.43
}
```

Building your model
===================
This library depends on nanopb (https://github.com/nanopb/nanopb). This means that you have to install nanopb library
before use Protocol Buffers Stream.

Installing nanopb
-----------------
If you are using platformio, just execute:
```
platformio lib install 431
```

If you prefer a manual install, you should copy those files into your project from https://github.com/nanopb/nanopb:
```
pb.h
pb_common.h
pb_decode.h
pb_decode.c
pb_encode.h
pb_encode.c
```

Google Protocol Buffers Documentation
-------------------------------------
Check the official documentation (https://developers.google.com/protocol-buffers/) if you dont know how protocol buffers
work
