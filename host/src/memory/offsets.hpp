#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include "memory.h"

#define SIG_SCAN( module_info, name, pattern, mask, offset ) \
    name = memory::signature_scan( memory::base_module, pattern ); \
    name = memory::read< std::uintptr_t >( name + offset ); 

namespace offsets {
    bool init( );

    inline std::uintptr_t uworld{ 0x117105c8 };
    inline std::uintptr_t game_instance{ 0x1D8 };
    inline std::uintptr_t persistent_level{ 0x30 };
    inline std::uintptr_t local_players{ 0x38 };
    inline std::uintptr_t player_controller{ 0x30 };
    inline std::uintptr_t local_pawn{ 0x338 };
    inline std::uintptr_t pawn_private{ 0x308 };
    inline std::uintptr_t root_component{ 0x198 };
    inline std::uintptr_t relative_location{ 0x120 };
    inline std::uintptr_t relative_rotation{ };
    inline std::uintptr_t component_velocity{ 0x168 };
    inline std::uintptr_t player_state{ 0x2b0 };
    inline std::uintptr_t team_index{ 0x1211 };
    inline std::uintptr_t game_state{ 0x160 };
    inline std::uintptr_t player_array{ 0x2a8 };
    inline std::uintptr_t mesh{ 0x318 };
    inline std::uintptr_t component_to_world{ 0x1c0 };
    inline std::uintptr_t bone_array{ 0x5B8 };
    inline std::uintptr_t bone_array_cache{ };
    inline std::uintptr_t last_submit_time{ };
    inline std::uintptr_t last_submit_time_on_screen{ };
}

bool offsets::init( ) {
    return true;
}

#endif 