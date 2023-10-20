#ifndef rio
#define rio

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Transfers up to n bytes of current file pos of fd
 * to location usrbuf.
 *
 * Returns num bytes transferred if OK, 0 on EOF, -1 on error.
 */
ssize_t rio_readn(int fd, void *usrbuf, size_t n);

/*
 * Transfers up to n bytes from usrbuf to fd.
 *
 * Returns num bytes transferred if OK, -1 on error.
 */
ssize_t rio_writen(int fd, void *usrbuf, size_t n);

#endif
