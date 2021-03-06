#ifndef	__unp_h
#define	__unp_h
#include "config.h"

extern "C" {
#include <errno.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>	/* inet(3) functions */
#include <sys/un.h>
#include <poll.h>		/* for convenience */
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <netdb.h>
}
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
					/* default file access permissions for new files */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
					/* default permissions for new directories */

typedef	void	Sigfunc(int);	/* for signal handlers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))


/* Following shortens all the typecasts of pointer arguments: */
#define	SA	struct sockaddr

/* Following could be derived from SOMAXCONN in <sys/socket.h>, but many
   kernels still #define it as 5, while actually supporting many more */
#define	LISTENQ		1024	/* 2nd argument to listen() */

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

/* Define some port number that can be used for our examples */
#define	SERV_PORT		 9877			/* TCP and UDP */
#define	SERV_PORT_STR	"9877"			/* TCP and UDP */
#define	UNIXSTR_PATH	"/tmp/unix.str"	/* Unix domain stream */
#define	UNIXDG_PATH		"/tmp/unix.dg"	/* Unix domain datagram */

namespace  unp
{
    // error.cc
    void  err_ret(const char *fmt, ...);
    void  err_sys(const char *fmt, ...);
    void  err_dump(const char *fmt, ...);
    void  err_msg(const char *fmt, ...);
    void  err_quit(const char *fmt, ...);
    // sock_ntop.cc
    char* Sock_ntop(const struct sockaddr *sa, socklen_t salen);
    // wrapsock.cc
    int   Accept(int fd, struct sockaddr *sa, socklen_t *salenptr);
    int   Bind(int fd, const struct sockaddr *sa, socklen_t salen);
    int   Connect(int fd, const struct sockaddr *sa, socklen_t salen);
    int   Getpeername(int fd, struct sockaddr *sa, socklen_t *salenptr);
    int   Getsockname(int fd, struct sockaddr *sa, socklen_t *salenptr);
    int   Listen(int fd, int backlog);
    int   Poll(struct pollfd *fdarray, unsigned long nfds, int timeout);
    int   Select(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
    int   Socket(int family, int type, int protocol);
    int   Shutdown(int fd, int how);
    int   Setsockopt(int fd, int level, int optname, const void *optval, socklen_t optlen);
    int   Getsockopt(int fd, int level, int optname, void *optval, socklen_t *optlenptr);
    ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags);
    ssize_t Recvfrom(int fd, void *ptr, size_t nbytes, int flags, struct sockaddr *sa, socklen_t *salenptr);
    ssize_t Recvmsg(int fd, struct msghdr *msg, int flags);
    ssize_t Send(int fd, const void *ptr, size_t nbytes, int flags);
    ssize_t Sendto(int fd, const void *ptr, size_t nbytes, int flags, const struct sockaddr *sa, socklen_t salen);
    ssize_t Sendmsg(int fd, const struct msghdr *msg, int flags);
    int     Socketpair(int family, int type, int protocol, int *fd);

    // wrapunix.cc
    int     Close(int fd);
    int     Ioctl(int fd, int request, void *arg);
    pid_t   Fork(void);
    void*   Malloc(size_t size);
    void*   Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    int     Open(const char *pathname, int oflag, mode_t mode);
    int     Pipe(int *fds);
    ssize_t Read(int fd, void *ptr, size_t nbytes);
    int     Sigaddset(sigset_t *set, int signo);
    int     Sigdelset(sigset_t *set, int signo);
    int     Sigemptyset(sigset_t *set);
    int     Sigfillset(sigset_t *set);
    int     Sigismember(const sigset_t *set, int signo);
    int     Sigpending(sigset_t *set);
    int     Sigprocmask(int how, const sigset_t *set, sigset_t *oset);
    char*   Strdup(const char *str);
    int     Unlink(const char *pathname);
    pid_t   Wait(int *iptr);
    pid_t   Waitpid(pid_t pid, int *iptr, int options);
    ssize_t Write(int fd, void *ptr, size_t nbytes);
    int     Fcntl(int fd, int cmd, int arg);
    int     Dup2(int fd1, int fd2);

    //writen.cc
    ssize_t Writen(int fd, void *ptr, size_t nbytes);
    // str_echo.cc
    void str_echo(int sockfd);
    //wraplib.cc
    const char* Inet_ntop(int family, const void *addrptr, char *strptr, size_t len);
    int Inet_pton(int family, const char *strptr, void *addrptr);
    //str_cli.cc
    void str_cli(FILE *fp, int sockfd);
    //wrapstdio.cc
    int   Fclose(FILE *fp);
    FILE* Fdopen(int fd, const char *type);
    char* Fgets(char *ptr, int n, FILE *stream);
    FILE* Fopen(const char *filename, const char *mode);
    int   Fputs(const char *ptr, FILE *stream);
    //readline.cc
    ssize_t Readline(int fd, void *ptr, size_t maxlen);
    //signal.cc
    Sigfunc* Signal(int signo, Sigfunc *func);
    //sockfd_to_family.cc
     int sockfd_to_family(int sockfd);
   //dg_cli.cc
   void dg_cli(FILE *fp, int sockfd, const SA *pservaddr, socklen_t servlen);
   //dg_echo.cc
   void dg_echo(int sockfd, struct sockaddr* pcliaddr, socklen_t clilen);
   //host_serv.cc
   struct addrinfo* Host_serv(const char* host, const char* serv, int family, int socktype);
   //tcp_connect.cc
   int Tcp_connect(const char *host, const char *serv);
   //tcp_listen.cc
   int Tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);
   //udp_client.cc
   int Udp_client(const char *host, const char *serv, SA **saptr, socklen_t *lenptr);
   //udp_connect.cc
   int Udp_connect(const char *host, const char *serv);
   //udp_server.cc
   int Udp_server(const char *host, const char *serv, socklen_t *addrlenp);
   //read_fd.cc
   ssize_t Read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
   //write_fd.cc
   ssize_t Write_fd(int fd, void *ptr, size_t nbytes, int sendfd);
}

#endif
