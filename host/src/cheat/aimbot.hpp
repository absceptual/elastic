#ifndef AIMBOT_HPP
#define AIMBOT_HPP

#include <cstdint>
#include <string_view>

#include "../memory/memory.h"

namespace aimbot {
    class mouse_t { 
        private:
            bool m_ready;
            std::int32_t m_conn;
            std::string_view m_address;
            std::int32_t m_port;

            bool send( std::string_view message ) const;

        public:
            mouse_t( );
            ~mouse_t( );

            bool move(  std::int32_t x,  std::int32_t y ) const;
            bool is_ready( ) const;
    };

    inline mouse_t* mouse;
    bool init( );
}

#endif