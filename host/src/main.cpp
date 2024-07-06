#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

#include "memory/memory.h"
#include "memory/offsets.hpp"
#include "engine/engine.hpp"
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
		auto game_state = world->GetGameState( );
		auto entity_count = game_state->GetPlayerCount( );
		for (int i = 0; i < entity_count; ++i) {
			auto player_state = game_state->GetPlayerState( i );
			auto pawn = player_state->GetPawn( );
			auto mesh = pawn->GetMesh( );
			auto location = mesh->GetBoneTransform( 109 );

			// std::cout << "(" << location.x << ", " << location.y << ", " << location.z << ")\n";
			auto local_player_position = world->GetOwningGameInstance( )
				->GetLocalPlayer( )
				->GetPlayerController( )
				->GetPawn( )
				->GetMesh(  )
				->GetBoneTransform( 109 );
			auto difference = location - local_player_position;
			std::cout << "distance from you: " << sqrt( pow(difference.x, 2) + pow(difference.y, 2) + pow(difference.z, 2) ) << '\n';
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