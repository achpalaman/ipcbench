#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

#include "callbacks.h"
#include "helpers.h"

extern uv_loop_t *loop;

void tcp_conn_cb(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "tcp_conn_cb error: %s\n", uv_strerror(status));
        return;
    }

    // initialize the client
    uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
    uv_tcp_init(loop, client);

    int err = uv_accept(server, (uv_stream_t*)client);
    if (err != 0) {
        fprintf(stderr, "uv_accept error: %s\n", uv_strerror(err));
        uv_close((uv_handle_t*)client, NULL);
    }

    uv_read_start((uv_stream_t*)client, alloc_cb, read_cb);
}

void uds_conn_cb(uv_stream_t *server, int status) {
    if (status < 0) {
        fprintf(stderr, "tcp_conn_cb error: %s\n", uv_strerror(status));
        return;
    }

    // initialize the client
    uv_pipe_t *client = (uv_pipe_t*) malloc(sizeof(uv_pipe_t));
    int err = uv_pipe_init(loop, client, 0);
    if (err != 0) {
        fprintf(stderr, "uv_pipe_init error: %s\n", uv_strerror(err));
    }

    err = uv_accept(server, (uv_stream_t*)client);
    if (err != 0) {
        fprintf(stderr, "uv_accept error: %s\n", uv_strerror(err));
        uv_close((uv_handle_t*)client, NULL);
    }

    uv_read_start((uv_stream_t*)client, alloc_cb, read_cb);
}

void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf) {
    if (nread > 0) {
        // There is data to read
        uv_buf_t wbuf[] = {
            { .base = &buf->base[0], .len = 1 }
        };
        //uv_write_t req;
        //uv_write(&req, client, wbuf, 1, write_cb);
        return;
    }
    else if (nread == UV_EOF) {
        fprintf(stderr, "read_cb EOF\n");
        uv_close((uv_handle_t*) client, NULL);
    }
    else if (nread < 0) {
        fprintf(stderr, "read_cb error:%s\n", uv_err_name(nread));
        uv_close((uv_handle_t*) client, NULL);
    }

    free(buf->base);
}

void write_cb(uv_write_t* req, int status) {
    if (status != 0) {
        fprintf(stderr, "write_cb error:%s\n", uv_strerror(status));
    }
    // Did not malloc any buffers for write, so no need to free!
}
