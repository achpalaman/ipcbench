void tcp_conn_cb(uv_stream_t *server, int status);
void uds_conn_cb(uv_stream_t *server, int status);
void read_cb(uv_stream_t *client, ssize_t nread, const uv_buf_t *buf);
void write_cb(uv_write_t* req, int status);
