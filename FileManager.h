#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Network.h"

class FileManager {
public:
    static void save(Network* network);
    static void load(Network* network);
};

#endif
