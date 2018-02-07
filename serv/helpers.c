#include <stdlib.h>
#include <uv.h>

#include "helpers.h"

void alloc_cb(uv_handle_t *handle, size_t suggested_size, uv_buf_t *buf) {
    // Assume allocation does not fail
    buf->base = (char*) malloc(suggested_size);
    buf->len = suggested_size;
}
