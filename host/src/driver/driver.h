#ifndef DRIVER_H
#define DRIVER_H

#include <iostream>
#include <cstdint>
#include <memory>

#include "memflow.hpp"
#include "process.h"

class Driver {
public:
    Inventory* inventory{ };
    ConnectorInstance<> connector, *connection = &connector;
    OsInstance<> os{ };
    MemoryView memory_view{ };

public:
    Driver( );

    Process find_fortnite(  );
    OsInstance<> get_os( );

};

#endif