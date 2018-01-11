#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "jhead.h"


int exif_stream_getc(exif_Stream* stream) {
  if (stream->fp) {
    return fgetc(stream->fp);
  } else {
    int c = stream->buf[stream->offset];
    stream->offset++;
    return c;
  }
}
int exif_stream_read(void* ptr, size_t size, size_t nmemb, exif_Stream* stream) {
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
int exif_stream_tell(exif_Stream* stream) {
  if (stream->fp) {
    return ftell(stream->fp);
  } else {
    return stream->offset;
  }
}
int exif_stream_seek(exif_Stream* stream, long offset, int mark) {
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

void exif_stream_close(exif_Stream* stream) {
  if (stream->fp) {
    fclose(stream->fp);
  }
}
