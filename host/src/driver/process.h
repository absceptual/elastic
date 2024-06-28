#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <cstdint>

#include "memflow.hpp"

class Process {
private:
    ProcessInstance<> m_instance{ };
public:
    Process(ProcessInstance<> instance);

    void find_module(std::string module_name);
};

#endif