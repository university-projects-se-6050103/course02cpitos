#include <cstdio>

#pragma once

class AbstractSocket {
public:

    AbstractSocket() { }

    virtual void listen(const char *host, int port) { }

    virtual AbstractSocket &accept() { return *new AbstractSocket; }

    virtual void connect(const char *host, int port) { }

    virtual void write(const char *message) { }

    virtual const char *read() { return NULL; }

    virtual void close() { }
};


void f();

AbstractSocket &createSocket();
