#include "unixsocket.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stddef.h>
#include <string.h>

UNIXSocket::UNIXSocket()
{
    m_iListenFd = unix_socket_listen(SERVER_NAME);
    if (m_iListenFd < 0) {
        //error
    }
    //cfilter run as lp
    int ret = chmod(SERVER_NAME, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IWGRP | S_IXGRP | S_IROTH | S_IWOTH | S_IXOTH);
    if (ret < 0) {

    }
}

int UNIXSocket::waitClient(uid_t *uidptr) {
    return unix_socket_accept(m_iListenFd, uidptr);
}

int UNIXSocket::unix_socket_listen(const  char *servername){
    int fd;
    struct sockaddr_un un;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        return (-1);
    }
    int rval;
    unlink(servername);
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, servername);
    if (bind(fd, (struct sockaddr *)&un, sizeof(struct sockaddr_un)) < 0) {
        rval = -2;
    } else {
        if (listen(fd, MAX_CONNECTION_NUMBER) < 0) {
            rval = -3;
        } else {
            return fd;
        }
    }
    int err;
    err = errno;
    close(fd);
    errno = err;
    return rval;
}

int UNIXSocket::unix_socket_accept(int listenfd, uid_t *uidptr) {
    int clifd, rval;
    struct sockaddr_un un;
    struct stat statbuf;
    socklen_t len;
    len = sizeof(un);
    if ((clifd = accept(listenfd, (struct sockaddr *)&un, &len)) < 0) {\
        return (-1);
    }
    if (stat(un.sun_path, &statbuf) < 0) {
        rval = -2;
    } else {
        if (S_ISSOCK(statbuf.st_mode)) {
            if (uidptr != NULL) *uidptr = statbuf.st_uid;
            unlink(un.sun_path);
            return clifd;
        } else {
            rval = -3;
        }
    }
    int err;
    err = errno;
    close(clifd);
    errno = err;
    return rval;
}

int UNIXSocket::unix_socket_recv(int fd, char *buf, int buf_len) {
    ssize_t recv_cnt = 0;
    while (recv_cnt < buf_len) {
        ssize_t cnt = recv(fd, buf + recv_cnt, buf_len - recv_cnt, 0);
        if (cnt == 0) { //connection closed by other side
            break;
        } else if (cnt > 0) {
            recv_cnt += cnt;
        } else {
            if (errno == EINTR || errno == EAGAIN)
                continue;
            else
                break;
        }
    }
    return !(recv_cnt == buf_len);
}

int UNIXSocket::unix_socket_send(int fd, const char *buf, int buf_len) {
    ssize_t send_cnt = 0;
    while (send_cnt < buf_len) {
        ssize_t cnt = send(fd, buf + send_cnt, buf_len - send_cnt, 0);
        if (cnt >= 0) {
            send_cnt += cnt;
        } else {
            if (errno == EINTR || errno == EAGAIN)
                continue;
            else
                break;
        }
    }
    return !(send_cnt == buf_len);
}

int UNIXSocket::sendMsg(int fd,const char *buf, int buf_len) {
    int res = unix_socket_send(fd, (char *)&buf_len, 4);  //use unix domain socket not care buf_len's endian
    if (res) return -1;
    return unix_socket_send(fd, buf, buf_len);
}

int UNIXSocket::recvMsg(int fd, char *buf) {
    char str_len[4];
    int res = unix_socket_recv(fd, str_len, 4);
    int len = *((int *)str_len);
    if (res || len > MAX_MSG_LEN || len < MIN_MSG_LEN) return -1;
    res = unix_socket_recv(fd, buf, len);
    return (res == 0) ? len: -1;
}
