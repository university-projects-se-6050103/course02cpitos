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
    printf("put %s into %s", value, key);
    return (char *) "OK";
}

char *Storage::getFrom(char *key) {
    char *value = storageMap.find(key)->first;
    printf("get from %s value %s", key, value);
    return value;
}
