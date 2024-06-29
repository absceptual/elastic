#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <mutex>
#include <vector>

#include "memflow.hpp"

#define STR( name ) CSliceRef< uint8_t >{ name }

namespace memory {
    inline std::mutex m{ };
    inline std::uintptr_t base{ };

    inline Inventory* inventory{ };
    inline ConnectorInstance< > connector, *connection = &connector;
    inline OsInstance< > os{ };
    inline MemoryView memory_view{ };
    inline ProcessInfo info{ }; // change back to ProcessInfo* if CR3 no longer works
    inline ProcessInstance< > instance{ };
    inline IntoProcessInstance< > process{ };
    
    bool init( );
    bool attach( );
    ModuleInfo get_module( std::string module_name );

    template < typename T >
    inline T read( std::uintptr_t address ) {
        std::lock_guard< std::mutex > l( m );

        T output{ };
        if ( !base )
            return output;

        process.read_raw_into( address, CSliceMut< uint8_t >( reinterpret_cast< char* >( &output ), sizeof( T ) ) );
        return output;
    }

    template < typename T >
    inline T read_chain( uint64_t address, std::vector< size_t > offsets ) {
        for ( auto offset : offsets ) {
            address += offset;
            address = read< std::uintptr_t >( address );
        }

        return read< T >( address );
    }


    template < typename T >
    inline bool write( std::uintptr_t address, const T& value )
    {
        std::lock_guard< std::mutex > l( m );
        return base && process.write_raw( address, CSliceRef< uint8_t >( reinterpret_cast< char * >( &value ), sizeof( T ) ) ) == 0;
    }

    template <typename T>
    inline T write_chain( uint64_t address, std::vector< size_t > offsets, const T& value ) {
        for ( auto offset : offsets ) {
            address += offset;
            address = read< std::uintptr_t >( address );
        }

        return write< T >( address, value );
    }

    std::vector< uintptr_t > signature_scan( ModuleInfo module_info, std::string pattern, std::string mask );
    
}

#endif