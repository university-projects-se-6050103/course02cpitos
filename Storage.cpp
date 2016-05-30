//
// Created by vlad on 30.05.16.
//

#include <map>
#include "Storage.h"

std::map<char *, char *> storageMap;

Storage::Storage() {

};

char *Storage::putInto(char *key, char *value) {
    storageMap[key] = value;
    return (char *) "OK";
}

char *Storage::getFrom(char *key) {
    return storageMap.find(key)->first;
}


