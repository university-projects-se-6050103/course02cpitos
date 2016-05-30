//
// Created by vlad on 30.05.16.
//


#include <iostream>
#include "AbstractSocket.cpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <fcntl.h>

using namespace std;

class Socket : public AbstractSocket {
private:
    // Створюємо екземпляр прослуховуючого сокета:
    typedef int SOCKET; // В Unix типу даних SOCKET немає
    SOCKET socket;

    struct sockaddr socketAddr;

    Socket(SOCKET socket) : AbstractSocket() {
        this->socket = socket;
    }

public:
    Socket() : AbstractSocket() {
        socket = ::socket(AF_INET, SOCK_STREAM, 0);
    }

    virtual void listen(const char *host, int port);

    virtual AbstractSocket &accept();

    virtual void connect(const char *host, int port);

    virtual void write(const char *message);

    virtual const char *read();

    virtual void close();
};

AbstractSocket &createSocket() {
    return *new Socket;
}

void Socket::listen(const char *host, int port) {
    cerr << "I'm listening to port " << port << " at host " << host << endl;

    struct sockaddr_in my_serv_addr;
    std::memset(&my_serv_addr, 0, sizeof(sockaddr_in));
    my_serv_addr.sin_family = AF_INET;
    my_serv_addr.sin_port = htons((uint16_t) port);
    my_serv_addr.sin_addr.s_addr = inet_addr(host);

    // Присвоюємо прослуховуючому сокету ІР-адресу і порт:
    bind(socket, (const struct sockaddr *) &my_serv_addr, sizeof(my_serv_addr));

    // Розпочинаємо процес прослуховування, дозволяючи одночасне під'єднання не більше 5 клієнтських сокетів:
    ::listen(socket, 5);
}

AbstractSocket &Socket::accept() {
    std::unique_ptr<Socket> client(new Socket());

    cerr << "accept" << endl;
    socklen_t sockStructSize = sizeof(struct sockaddr);

    // Set the socket to a nonblocking mode
    fcntl(socket, F_SETFL, O_NONBLOCK);

    SOCKET sock = ::accept(socket, &socketAddr, &sockStructSize);
    //set accept socket address
    client->socketAddr = socketAddr;
    //set accept socket handler
    client->socket = sock;
    return ((AbstractSocket &) *client.release());
}

void Socket::connect(const char *host, int port) {
    cerr << "I'm connecting to port " << port << " at host " << host << endl;
    //create new socket
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);    //socket is create?

    //god father socket
    struct sockaddr_in serverAddress;
    std::memset(&serverAddress, 0, sizeof(sockaddr_in));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons((uint16_t) port);
    serverAddress.sin_addr.s_addr = inet_addr(host);

    ::connect(sock, (const struct sockaddr *) &serverAddress, sizeof(serverAddress));
}

void Socket::write(const char *message) {
    cerr << "Send message " << message << endl;
    cout << message << endl;
    ::send(socket, message, sizeof(message), 0);
}

const char *Socket::read() {
    char *buf = new char[1024];

    fd_set read_flags, write_flags;
    FD_ZERO(&read_flags);
    FD_ZERO(&write_flags);
    FD_SET(socket, &read_flags);
    FD_SET(socket, &write_flags);
    FD_SET(STDIN_FILENO, &read_flags);
    FD_SET(STDIN_FILENO, &write_flags);

    if (FD_ISSET(socket, &read_flags)) {
        //clear set
        FD_CLR(socket, &read_flags);
        buf[recv(socket, buf, sizeof(buf), 0)] = 0;
    }

    return buf;
}

void Socket::close() {
    ::shutdown(socket, 0);
    ::close(socket);
}