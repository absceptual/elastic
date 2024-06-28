#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <cstdint>
#include <memory>

#include "memflow.hpp"

class Process {
public:
   IntoProcessInstance<> m_process{ };
   std::shared_ptr<ProcessInstance<>> m_instance{ };
   const ProcessInfo* m_info{ };
   std::uintptr_t m_eprocess{ };
   std::uint32_t m_pid{ };
   std::string m_name{ };
   std::string m_path{ };
   std::uintptr_t m_base{ };
   
public:
    Process() = default;
    Process(std::shared_ptr<ProcessInstance<>> instance, OsInstance<>& os);

    ModuleInfo find_module(std::string module_name);
    std::uintptr_t get_base_module();
    std::uintptr_t get_eprocess();
    std::uint32_t get_pid( );
    std::string get_name( );
    std::string get_path( );
    const ProcessInfo* get_info( ); 
    std::uintptr_t get_base( );

    
};

#endif