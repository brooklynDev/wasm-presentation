#define EXPORT __attribute__((visibility("default")))

typedef struct __wasi_ciovec_t
{
    const void *buf;
    long buf_len;
} __wasi_ciovec_t;

__attribute__((import_module("wasi_unstable"), import_name("fd_write"))) 
extern char __wasi_fd_write(long fd, const __wasi_ciovec_t *iovs,long iovs_len,long *nwritten);

__wasi_ciovec_t iov = {
    .buf = "Hello, World!\n",
    .buf_len = 14
};

EXPORT void hello_world(void)
{
    long num;
    __wasi_fd_write(1, &iov, 1, &num);
}
