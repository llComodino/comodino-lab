#include <sys/socket.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#define MAXLINE 4096
#define PORT 8080
#define IP "127.0.0.1"

#define SA struct sockaddr

void err_n_die(const char *fmt, ...);

int main (void) {
    
    int sockfd, n;
    int sendbytes;
    struct sockaddr_in servaddr;
    char sendline[MAXLINE];
    char recvline[MAXLINE];
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        err_n_die("Error while creating socket");
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    
    if (inet_pton(AF_INET, IP, &servaddr.sin_addr) <= 0) {
        err_n_die("inet_pton error for %s", IP);
    }
    
    if (connect(sockfd, (SA *) &servaddr, sizeof(servaddr)) < 0) {
        err_n_die("connect failed");
    }
    
    sprintf(sendline, "GET / HTTP/1.1\r\n\r\n");
    sendbytes = strlen(sendline);
    
    if (write(sockfd, sendline, sendbytes) != sendbytes) {
        err_n_die("write error");
    }
    
    memset(recvline, 0, MAXLINE);
    
    while ((n = read(sockfd, recvline, MAXLINE - 1)) > 0) {
        printf("%s", recvline);
        memset(recvline, 0, MAXLINE);
    }
    
    if (n < 0) {
        err_n_die("read error");
    }
    
    exit(0);
}

void err_n_die(const char *fmt, ...) {
  int errno_save;
  va_list ap;

  errno_save = errno;

  va_start(ap, fmt);
  vfprintf(stdout, fmt, ap);
  fprintf(stdout, "\n");
  fflush(stdout);

  if (errno_save != 0) {
    fprintf(stdout, "(errno = %d) : %s\n", errno_save, strerror(errno_save));
    fprintf(stdout, "\n");
    fflush(stdout);
  }

  va_end(ap);
  exit(1);
}
