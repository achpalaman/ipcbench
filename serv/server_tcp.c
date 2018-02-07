// Compile with gcc -luv
#include <stdio.h>
#include <stdlib.h>
#include <uv.h>

#include "callbacks.h"

uv_loop_t *loop;

int main() {
    loop = uv_default_loop();

    // Declare and initialize server
    uv_tcp_t server;
    uv_tcp_init(loop, &server);

    // Declare and initialize host:port struct
    struct sockaddr_in addr;
    uv_ip4_addr("0.0.0.0", 9890, &addr);

    //           server,                   addr,     flags
    uv_tcp_bind(&server, (const struct sockaddr*)&addr, 0);

    int err = uv_listen((uv_stream_t *)&server, 128, tcp_conn_cb);
    if (err != 0) {
        fprintf(stderr, "uv_listen error: %s\n", uv_strerror(err));
        return 1;
    }

    return uv_run(loop, UV_RUN_DEFAULT);
}
