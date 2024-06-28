#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <cstdint>

#include "memflow.hpp"
#include "process.h"

class Driver {
private:
    Inventory* inventory{ };
    ConnectorInstance<> connector, *connection = &connector;
    OsInstance<> os{ };

public:
    Driver( );

    Process find_process(std::string process_name);
};

#endif