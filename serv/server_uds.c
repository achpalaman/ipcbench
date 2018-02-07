// Compile with gcc -luv
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

#include "callbacks.h"

uv_loop_t *loop;

int main() {
    loop = uv_default_loop();

    // Declare and initialize server
    uv_pipe_t server;
    int err = uv_pipe_init(loop, &server, 0);
    if (err != 0) {
        fprintf(stderr, "uv_pipe_init error: %s\n", uv_strerror(err));
    }

    // Declare the path
    const char *path = "tmp.out";

    err = uv_pipe_bind(&server, path);
    if (err != 0) {
        fprintf(stderr, "uv_pipe_bind error: %s\n", uv_strerror(err));
    }

    err = uv_listen((uv_stream_t *)&server, 128, uds_conn_cb);
    if (err != 0) {
        fprintf(stderr, "uv_listen error: %s\n", uv_strerror(err));
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
