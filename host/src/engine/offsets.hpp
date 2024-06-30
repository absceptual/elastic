#ifndef OFFSETS_HPP
#define OFFSETS_HPP

#include "../memory/memory.h"

#define SIG_SCAN( module_info, name, pattern, mask, offset ) \
    name = memory::signature_scan( memory::base_module, pattern, mask )[ 0 ]; \
    name = memory::read< std::uintptr_t >( name + offset ); \
    if ( !name ) \
        return false; 

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

    if ( !memory::base_module.base )
        return false;

    SIG_SCAN( memory::base_module, offsets::uworld, "\x26\x0E\x02\x0B", "xxxx", 0 );
    std::cout << "[offsets::init] resolved uworld: 0x" << std::hex << offsets::uworld << '\n';

    SIG_SCAN( memory::base_module, offsets::game_instance, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved game_instance: 0x" << std::hex << offsets::game_instance << '\n';

    SIG_SCAN( memory::base_module, offsets::local_players, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved local_players: 0x" << std::hex << offsets::local_players << '\n';

    SIG_SCAN( memory::base_module, offsets::player_controller, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved player_controller: 0x" << std::hex << offsets::player_controller << '\n';

    SIG_SCAN( memory::base_module, offsets::local_pawn, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved local_pawn: 0x" << std::hex << offsets::local_pawn << '\n';

    SIG_SCAN( memory::base_module, offsets::pawn_private, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved pawn_private: 0x" << std::hex << offsets::pawn_private << '\n';

    SIG_SCAN( memory::base_module, offsets::root_component, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved root_component: 0x" << std::hex << offsets::root_component << '\n';
    
    SIG_SCAN( memory::base_module, offsets::relative_location, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved relative_location: 0x" << std::hex << offsets::relative_location << '\n';

    SIG_SCAN( memory::base_module, offsets::player_state, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved player_state: 0x" << std::hex << offsets::player_state << '\n';

    SIG_SCAN( memory::base_module, offsets::team_index, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved team_index: 0x" << std::hex << offsets::team_index << '\n';

    SIG_SCAN( memory::base_module, offsets::game_state, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved game_state: 0x" << std::hex << offsets::game_state << '\n';

    SIG_SCAN( memory::base_module, offsets::player_array, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved player_array: 0x" << std::hex << offsets::player_array << '\n';

    SIG_SCAN( memory::base_module, offsets::mesh, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved mesh: 0x" << std::hex << offsets::mesh << '\n';

    SIG_SCAN( memory::base_module, offsets::component_to_world, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved component_to_world: 0x" << std::hex << offsets::component_to_world << '\n';

    SIG_SCAN( memory::base_module, offsets::bone_array, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved bone_array: 0x" << std::hex << offsets::bone_array << '\n';

    SIG_SCAN( memory::base_module, offsets::bone_array_cache, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved bone_array_cache: 0x" << std::hex << offsets::bone_array_cache << '\n';

    SIG_SCAN( memory::base_module, offsets::last_submit_time, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved last_submit_time: 0x" << std::hex << offsets::last_submit_time << '\n';

    SIG_SCAN( memory::base_module, offsets::last_submit_time_on_screen, "\xFF", "x", 5 );
    std::cout << "[offsets::init] resolved last_submit_time_on_screen: 0x" << std::hex << offsets::last_submit_time_on_screen << '\n';

    return true;

}

#endif 