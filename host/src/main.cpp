#include <vector>
#include <thread>
#include <chrono>

#include "memory/memory.h"
#include "memory/offsets.hpp"
#include "engine/engine.hpp"
#include "cheat/aimbot.hpp"

int main( int argc, char *argv[ ] ) {

	if ( !memory::init( ) ) 
		return -1;

	std::cout << "[+] memflow initalized succesfully\n";

	if ( !aimbot::init( ) )
		return -1;

	std::cout << "[+] aimbot module initalized succesfully\n";

	std::cout << aimbot::mouse->move( 20000, 400 ) << '\n';

	std::cout << "[!] attempting to fix directory table base (cr3)\n";


	
	//if ( !memory::attach( ) )
		//return -2;

	

	/*
	std::cout << "[+] memflow attached to fortnite succesfully\n";

	std::uintptr_t va_text = 0;
	for (int i = 0; i < 25; i++) {
		std::int32_t address{ };

		if ( memory::read< std::int32_t >( memory::base + ( i * 0x1000 ) + 0x250 ) == 0x260E020B ) 
			va_text = memory::base + ( ( i + 1 ) * 0x1000 );
	}

	
	std::uintptr_t gworld = 0x117105c8 + va_text;
	std::cout << "[+] game information:" << '\n';
	std::cout << "\t[+] memory base address: 0x" << std::hex << memory::base << '\n';
	std::cout << "\t[+] gworld address: 0x" << std::hex << gworld << '\n';
	std::cout << "\t[+] uworld address: 0x" << std::hex << memory::read< std::uintptr_t >( gworld ) << '\n';
	
	auto world = memory::read< std::uintptr_t >( va_text + 0x117105c8 );
	std::cout << std::hex << world << '\n';

	auto game_instance = memory::read< std::uintptr_t >( world + 0x1d8 ); //world->GetOwningGameInstance( );
	std::cout << std::hex << game_instance << '\n';

	auto localplayer = memory::read< std::uintptr_t >( memory::read< std::uintptr_t >( game_instance + 0x38 ) ); // game_instance->GetLocalPlayer( );
	std::cout << std::hex << localplayer << '\n';

	auto playercontroller = memory::read< std::uintptr_t >( localplayer + 0x30 ); //localplayer->GetPlayerController( );
	std::cout << std::hex << playercontroller << '\n';

	auto pawn = memory::read< std::uintptr_t >( playercontroller + 0x338 ); 
	std::cout << std::hex << pawn << '\n';

	auto component =  memory::read< std::uintptr_t >( pawn + 0x198 ); 
	std::cout << std::hex << component << '\n';

	while ( true ) {
		std::uintptr_t address{ };
		//std::cout << "enter any address to read or -1 to exit: 0x";
		//std::cin >> std::hex >> address;

		if ( address == -1 ) 
			break;

		FVector position{ };
		{
			game_instance = memory::read< std::uintptr_t >( world + 0x1d8 ); //world->GetOwningGameInstance( );
			localplayer = memory::read< std::uintptr_t >( memory::read< std::uintptr_t >( game_instance + 0x38 ) ); // game_instance->GetLocalPlayer( );
			playercontroller = memory::read< std::uintptr_t >( localplayer + 0x30 ); //localplayer->GetPlayerController( );
			pawn = memory::read< std::uintptr_t >( playercontroller + 0x338 ); 
			component =  memory::read< std::uintptr_t >( pawn + 0x198 ); 
			position = memory::read< FVector >( component + 0x120 ); 
		}	
		std::cout << "(" << position.x << ", " << position.y << ", " << position.z << ")\n";

		if ( address == -2 ) {
			std::uint64_t output = memory::read< std::uint64_t >( address );
			std::cout << std::hex << address << " = " << std::hex << output << '\n';
		}
	}
	*/

	return 0;
}