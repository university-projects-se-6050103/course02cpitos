#include <iostream>
#include "AbstractSocket.cpp"
#include "EmitterListener.h"

using namespace std;

int main(int ac, char **av) {
    AbstractSocket &server = run_server();
    AbstractSocket &client = server.accept();
    cout << "server init" << endl;
    client.connect("127.0.0.1", 15591);
    client.write("PUT Ukraine Kyyiv");
    cerr << "I've received " << client.read() << endl;

//    client.close();
}
