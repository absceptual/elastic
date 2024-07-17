#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

#include "memory/memory.h"
#include "memory/offsets.hpp"
#include "engine/classes.hpp"
#include "utility/utility.h"
#include "cheat/aimbot.hpp"


int main( int argc, char *argv[ ] ) {

	if ( !memory::init( ) ) 
		return -1;

	std::cout << "[+] memflow initalized succesfully\n";
	std::cout << "[!] attempting to fix directory table base (cr3)\n";

	if ( !memory::attach( ) )
		return -2;

	std::cout << "[+] memflow attached to fortnite succesfully\n";

	auto world = UWorld::GetUWorld( );
	while (true) {
		AGameState* game_state 		  = world->GetGameState( );
		APlayerController* controller = world->GetOwningGameInstance( )->GetLocalPlayer( )->GetPlayerController( );
		APawn* pawn 				  = controller->GetPawn( );
		
		for (std::uint32_t i = 0; i < game_state->GetPlayerCount( ); ++i) {
			APlayerState* player_state = game_state->GetPlayerState( i );

			if ( player_state == pawn->GetPlayerState( ) )
				continue;

			auto pawn = player_state->GetPawn( );
			auto mesh = pawn->GetMesh( );
			auto head = mesh->GetBoneTransform( 109 );

			std::cout << utils::world_to_screen( head ) << '\n';
		}
		
		std::this_thread::sleep_for( std::chrono::seconds(1));
	}
	

	/*
	while ( true ) {
		std::uintptr_t address{ };
		//std::cout << "enter any address to read or -1 to exit: 0x";
		//std::cin >> std::hex >> address;

		if ( address == -1 ) 
			break;
			
		if ( address == -2 ) {
			std::uint64_t output = memory::read< std::uint64_t >( address );
			std::cout << std::hex << address << " = " << std::hex << output << '\n';
		}
	}
	*/

	return 0;
}