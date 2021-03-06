
#include <Arduino.h>
#include <pb_encode.h>
#include <pb_decode.h>

#ifndef PROTOCOLBUFFERSSTREAM_H
#define PROTOCOLBUFFERSSTREAM_H


class ProtocolBuffersStream {
  private:
    Stream *stream_;
    unsigned int timeout_;
    /* The following static stuff are functions required by protocol buffers library
       because it expects a function
    */
    static bool callbackWrite(pb_ostream_t *stream, const uint8_t *buf, size_t count);
    static bool callbackRead(pb_istream_t *stream, uint8_t *buf, size_t count);

  public:
    ProtocolBuffersStream(Stream *stream, unsigned int timeout = 1000);
    void setTimeout(unsigned int timeout);
    bool receive(const pb_field_t fields[], void *dest_struct);
    bool send(const pb_field_t fields[], const void *src_struct);
    void flush();
    /* This variable are used in the static methods declared above */
    static size_t dataAvailable;
};



#endif //PROTOCOLBUFFERSSTREAM_H
