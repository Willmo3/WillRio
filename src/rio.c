#include "../include/rio.h"

ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
  size_t nleft = n;
  ssize_t nread;
  char *bufp = usrbuf;

  while (nleft > 0) {
    if ((nread = read(fd, bufp, nleft)) < 0) {
      // Check for interrupt by extraneous sig handler return.
      if (errno == EINTR)
        nread = 0;
      else
        return -1;
    }
    else if (nread == 0) 
      break;       // EOF
    
    nleft -= nread; // nleft will be 0 if sig handler return disrupted.
    bufp += nread;
  }

  return n;
}

ssize_t rio_writen(int fd, void *usrbuf, size_t n) {
  size_t nleft = n;
  size_t nwritten;
  char *bufp = usrbuf;

  while (nleft > 0) {
    if ((nwritten = write(fd, bufp, nleft)) <= 0) {
      // Check for interrupt by extraneous sig handler return.
      if (errno == EINTR)
        nwritten = 0;
      else
        return -1;
    }
    nleft -= nwritten;
    bufp += nwritten;
  }
  return n;
}

void rio_readinitb(rio_t *rp, int fd) {
  rp->rio_fd = fd;
  rp->rio_cnt = 0;
  rp->rio_bufptr = rp->rio_buf;
}

// INTERNAL FNS

static ssize_t rio_read(rio_t *rp, char *usrbuf, size_t n) {
  int cnt;

  while (rp->rio_cnt <= 0) { // Refill if buf empty
    rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));

    if (rp->rio_cnt < 0 && errno != EINTR) {
      return -1; // Interrupted by sig handler return
    }
    else if (rp->rio_cnt == 0) // EOF
      return 0;
    else
      rp->rio_bufptr = rp->rio_buf; // Reset buffer ptr.
  }

  // Copy min(n, rp->rio_cnt) bytes from internal buf to user buf.
  cnt = n;
  if (rp->rio_cnt < n)
    cnt = rp->rio_cnt;
  
  assert(memcpy(usrbuf, rp->rio_bufptr, cnt) != 0); 
  rp->rio_bufptr += cnt;
  rp->rio_cnt -= cnt;
  return cnt;
}
