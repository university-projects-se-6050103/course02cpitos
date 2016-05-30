//
// Created by vlad on 30.05.16.
//

#ifndef COURSE02LAB05OS_STORAGE_H
#define COURSE02LAB05OS_STORAGE_H

class Storage {

public:
    Storage();

    char *putInto(char *key, char *value);

    char *getFrom(char *key);
};


#endif //COURSE02LAB05OS_STORAGE_H
