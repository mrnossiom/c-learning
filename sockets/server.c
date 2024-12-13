#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#include "sock.h"

#define BACKLOG 5
#define BUF_SIZE 100

static int recv_fd(int socket_fd) {
  int data;
  int fd;

  struct iovec iov = {
      .iov_base = &data,
      .iov_len = sizeof(int),
  };

  struct msghdr msgh = {
      .msg_name = NULL,
      .msg_namelen = 0,

      .msg_iov = &iov,
      .msg_iovlen = 1,
  };

  union {
    char buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr align;
  } control_msg;
  struct cmsghdr *cmsgp;

  msgh.msg_control = control_msg.buf;
  msgh.msg_controllen = sizeof(control_msg.buf);

  if (recvmsg(socket_fd, &msgh, 0) == -1)
    return -1;

  cmsgp = CMSG_FIRSTHDR(&msgh);
  if (cmsgp == NULL || cmsgp->cmsg_len != CMSG_LEN(sizeof(int)) ||
      cmsgp->cmsg_level != SOL_SOCKET || cmsgp->cmsg_type != SCM_RIGHTS) {
    errno = EINVAL;
    return -1;
  }

  memcpy(&fd, CMSG_DATA(cmsgp), sizeof(int));
  return fd;
}

int main() {
  struct sockaddr_un addr;

  int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  assert(socket_fd != 0 && "could not create socket");

  assert(strlen(WP_SOCK_PATH) < sizeof(addr.sun_path) &&
         "server socket path too long");

  // Delete any file that already exists at the address. Make sure the deletion
  // succeeds. If the error is just that the file/directory doesn't exist, it's
  // fine.
  assert((remove(WP_SOCK_PATH) != -1 || errno == ENOENT) &&
         "there is already a file at the server socket path");

  // Zero out the address, and set family and path.
  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, WP_SOCK_PATH, sizeof(addr.sun_path) - 1);

  assert(bind(socket_fd, (struct sockaddr *)&addr,
              sizeof(struct sockaddr_un)) == 0 &&
         "could not bind socket to addr");

  assert(listen(socket_fd, BACKLOG) != -1);

  char buf[BUF_SIZE];
  ssize_t read_len;

  for (;;) {
    printf("$ waiting to accept a connection\n");

    // NOTE: blocks until a connection request arrives.
    int conn_fd = accept(socket_fd, NULL, NULL);

    int sent_fd = recv_fd(conn_fd);
    printf("recv fd %d, errno: %d\n", sent_fd, errno);
    assert(sent_fd != -1);

    write(sent_fd, "hello\n", 5);

    while ((read_len = read(conn_fd, buf, BUF_SIZE)) != 0) {
      // Then, write those bytes from buf into STDOUT.
      assert(write(STDOUT_FILENO, buf, read_len) == read_len &&
             "partial/failed write");
    }

    assert(read_len >= 0 && "error while reading");

    // TODO: could be non-terminating
    assert(close(conn_fd) == 0 && "could not close connection socket");
  }

  return 0;
}
