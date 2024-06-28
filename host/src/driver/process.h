#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <cstdint>
#include <memory>
#include <mutex>

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
   std::mutex m;

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

    template <typename T>
    inline bool read(uint64_t address, T &out)
    {
        std::lock_guard<std::mutex> l(m);
        return m_base && m_process.read_raw_into(address, CSliceMut<uint8_t>((char *)&out, sizeof(T))) == 0;
    }

    template <typename T>
    inline bool read_array(uint64_t address, T out[], size_t len)
    {
        std::lock_guard<std::mutex> l(m);
        return m_base && m_process.read_raw_into(address, CSliceMut<uint8_t>((char *)out, sizeof(T) * len)) == 0;
    }

    template <typename T>
    inline bool write(uint64_t address, const T &value)
    {
        std::lock_guard<std::mutex> l(m);
        return m_base && m_process.write_raw(address, CSliceRef<uint8_t>((char *)&value, sizeof(T))) == 0;
    }

    template <typename T>
    inline bool write_array(uint64_t address, const T value[], size_t len)
    {
        std::lock_guard<std::mutex> l(m);
        return m_base && m_process.write_raw(address, CSliceRef<uint8_t>((char *)value, sizeof(T) * len)) == 0;
    }
};

#endif