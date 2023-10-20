#ifndef rio
#define rio

#include <string.h>
#include <assert.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

// rio_t: special read buffer that fills itself from fd when empty.
#define RIO_BUFSIZE 8192
typedef struct {
    int rio_fd;        // Descriptor for internal buf
    int rio_cnt;       // Unread bytes in internal buf
    char *rio_bufptr;  // Next unread byte in internal buf
    char rio_buf[RIO_BUFSIZE];
} rio_t;

// Associates file desc with rb.
void rio_readinitb(rio_t *rb, int fd);

/*
 * Reads next text line from rp into usrbuf
 * Reads at most maxlen -1, appends null term.
 *
 * Returns num bytes read, 0 on EOF, -1 on error.
 */
ssize_t rio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

// Like readlineb, but instead transfers n raw bytes.
ssize_t rio_readnb(rio_t *rp, void *usrbuf, size_t n);

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
