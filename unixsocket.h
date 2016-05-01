#ifndef UNIXSOCKET_H
#define UNIXSOCKET_H

#include <sys/types.h>

class UNIXSocket
{
private:
    const int MAX_CONNECTION_NUMBER = 100;
    const char * const SERVER_NAME = "/tmp/server.sock";
    int m_iListenFd;
    int unix_socket_listen(const char *servername);
    int unix_socket_accept(int listenfd, uid_t *uidptr);
    int unix_socket_recv(int fd, char *buf, int buf_len);//0:success;!=0:failed
    int unix_socket_send(int fd,const char *buf, int buf_len);//0:success;!=0:failed

    const int MIN_MSG_LEN = 1;
    const int MAX_MSG_LEN = 1024;
public:
    UNIXSocket();
    int waitClient(uid_t *uidptr);
    int sendMsg(int fd, const char *buf, int buf_len); //if success return 0 else return < 0
    int recvMsg(int fd, char *buf); //if success return length of buf(may not '\0') else return < 0
};

#endif // UNIXSOCKET_H
