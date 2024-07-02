#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include "memory.h"

#define SIG_SCAN( module_info, name, pattern, mask, offset ) \
    name = memory::signature_scan( memory::base_module, pattern ); \
    name = memory::read< std::uintptr_t >( name + offset ); 

namespace offsets {
    bool init( );

    inline std::uintptr_t uworld{ };
    inline std::uintptr_t game_instance{ };
    inline std::uintptr_t local_players{ };
    inline std::uintptr_t player_controller{ };
    inline std::uintptr_t local_pawn{ };
    inline std::uintptr_t pawn_private{ };
    inline std::uintptr_t root_component{ };
    inline std::uintptr_t relative_location{ };
    inline std::uintptr_t player_state{ };
    inline std::uintptr_t team_index{ };
    inline std::uintptr_t game_state{ };
    inline std::uintptr_t player_array{ };
    inline std::uintptr_t mesh{ };
    inline std::uintptr_t component_to_world{ };
    inline std::uintptr_t bone_array{ };
    inline std::uintptr_t bone_array_cache{ };
    inline std::uintptr_t last_submit_time{ };
    inline std::uintptr_t last_submit_time_on_screen{ };
}

bool offsets::init( ) {
    return true;
}

#endif 