#include <iostream>
#include "AbstractSocket.cpp"
#include "EmitterListener.h"

using namespace std;

AbstractSocket &run_server() {
    AbstractSocket &server = createSocket();
    server.listen("127.0.0.1", 15591);
    return server;
}

AbstractSocket &run_client(AbstractSocket &server) {
    AbstractSocket &client = server.accept();
    client.connect("127.0.0.1", 15591);
    return client;
}