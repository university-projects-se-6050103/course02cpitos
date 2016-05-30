#include <iostream>
#include <zconf.h>
#include "AbstractSocket.cpp"
#include "EmitterListener.h"
#include "EventsHandler.h"

using namespace std;

int main(int ac, char **av) {
    AbstractSocket &server = run_server();
    AbstractSocket &client = run_client(server);
    EventsHandler *eventsHandler = new EventsHandler();

    client.write("PUT Ukraine Kyyiv");

    while (1) {
        usleep(1000000);
        eventsHandler->handle((char *) client.read());
    }


    client.close();
}
