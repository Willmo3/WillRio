#include "rio.h"

ssize_t rio_readn(int fd, void *usrbuf, size_t n) {
  size_t nleft = n;
  ssize_t nread;
  char *bufp = usrbuf;

  while (nleft > 0) {
    if ((nread = read(fd, bufp, nleft)) < 0) {
      // Check for interrupt by sig handler return.
      if (errno == EINTR)
        nread = 0;
      else
        return -1; // Unexpected error!
    }
    else if (nread == 0) 
      break;       // EOF
    
    nleft -= nread; // nleft will be 0 if sig handler return disrupted.
    bufp += nread;
  }

  return n;
}
