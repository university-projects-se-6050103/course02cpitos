//
// Created by vlad on 30.05.16.
//

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "EventsHandler.h"
#include "Storage.h"


using namespace std;

EventsHandler::EventsHandler() {

}

char *EventsHandler::handle(char *message) {
    Storage *storage = new Storage();
    message = (char *) "PUT Ukraine Kyyiv";
    string str(message);
    char *buf = nullptr; // Have a buffer string
    stringstream ss(str); // Insert the string into a stream

    vector<char *> tokens; // Create vector to hold our words

    bool isPut = false;
    bool isGet = false;

    while (ss >> buf) {
        if (string("PUT").compare(string(buf)) != 0) {
            tokens.push_back(buf);
            isPut = true;
        }

        if (string("GET").compare(string(buf)) != 0) {
            tokens.push_back(buf);
            isGet = true;
        }
    }

    if (isPut) {
        return storage->putInto(tokens.at(1), tokens.at(2));
    }

    if (isGet) {
        return storage->getFrom(tokens.at(1));
    }
}
