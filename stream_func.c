#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "jhead.h"


int stream_getc(_Stream* stream) {
  if (stream->fp) {
    return fgetc(stream->fp);
  } else {
    int c = stream->buf[stream->offset];
    stream->offset++;
    return c;
  }
}
int stream_read(void* ptr, size_t size, size_t nmemb, _Stream* stream) {
  if (stream->fp) {
    return fread(ptr, size, nmemb, stream->fp);
  } else {
    int aviable = size * nmemb;
    if ((stream->size - stream->offset) < aviable) {
      aviable = (stream->size - stream->offset);
    }
    memcpy(ptr, stream->buf + stream->offset, aviable);
    stream->offset += aviable;
    return aviable;
  }
}
int stream_tell(_Stream* stream) {
  if (stream->fp) {
    return ftell(stream->fp);
  } else {
    return stream->offset;
  }
}
int stream_seek(_Stream* stream, long offset, int mark) {
  if (stream->fp) {
    return fseek(stream->fp, offset, mark);
  } else {
    if (mark == SEEK_CUR) {
      stream->offset += offset;
    } else if (mark == SEEK_SET) {
      stream->offset = offset;
    } else if (mark == SEEK_END) {
      stream->offset = stream->size + offset;
    }
  }
}

void stream_close(_Stream* stream) {
  if (stream->fp) {
    fclose(stream->fp);
  }
}
