#include <iostream>
#include "AbstractSocket.cpp"
#include "EmitterListener.h"

using namespace std;

int main(int ac, char **av) {
    AbstractSocket &server = run_server();
    AbstractSocket &client = run_client(server);
    client.write("PUT Ukraine Kyyiv");
    cerr << "I've received " << client.read() << endl;

//    client.close();
}
