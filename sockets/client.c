#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <unistd.h>

#include "sock.h"

#define BUF_SIZE 100
#define SHM_PATH "/dev/shm/wayplain-buffer-0"

static int send_fd(int socket_fd, int fd) {
  int data = 0xDEADBEEF;
  struct iovec iov = {
      .iov_base = &data,
      .iov_len = sizeof(data),
  };

  union {
    char buf[CMSG_SPACE(sizeof(int))];
    struct cmsghdr align;
  } control_msg;

  struct msghdr msgh = {
      // no need for a name for ipc
      .msg_name = NULL,
      .msg_namelen = 0,

      .msg_iov = &iov,
      .msg_iovlen = 1,

      .msg_control = control_msg.buf,
      .msg_controllen = sizeof(control_msg.buf),
  };

  // build control message to pass through ancillary data
  // contains a fd
  struct cmsghdr *cmsgp;
  cmsgp = CMSG_FIRSTHDR(&msgh);
  cmsgp->cmsg_level = SOL_SOCKET;
  cmsgp->cmsg_type = SCM_RIGHTS;
  cmsgp->cmsg_len = CMSG_LEN(sizeof(int));
  memcpy(CMSG_DATA(cmsgp), &fd, sizeof(int));

  if (sendmsg(socket_fd, &msgh, 0) == -1)
    return -1;

  return 0;
}

int main() {
  struct sockaddr_un addr;

  // int shm_fd = shm_open(SHM_PATH, O_CREAT | O_EXCL | O_RDWR, 0600);
  // errno = 0;
  // perror("yolo");
  // assert(shm_fd != -1 && "could not open shm file");

  char buf[BUF_SIZE];
  ssize_t read_len;

  int socket_fd = socket(AF_UNIX, SOCK_STREAM, 0);
  assert(socket_fd != -1 && "could not create socket");

  memset(&addr, 0, sizeof(struct sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, WP_SOCK_PATH, sizeof(addr.sun_path) - 1);

  assert(connect(socket_fd, (struct sockaddr *)&addr,
                 sizeof(struct sockaddr_un)) != -1 &&
         "could not connect to socket");
  // write(1, "hello\n", 5);

  assert(send_fd(socket_fd, 1) != -1);

  while ((read_len = read(STDIN_FILENO, buf, BUF_SIZE)) > 0) {
    // Then, write those bytes from buf into the socket.
    assert(write(socket_fd, buf, read_len) == read_len);
  }

  assert(read_len != -1);

  // Closes our socket; server sees EOF.
  return 0;
}
