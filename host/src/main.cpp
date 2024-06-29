#include "memory/memory.h"
#include <vector>

#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {

	if ( !memory::init( ) ) 
		return -1;

	std::cout << "[+] memflow initalized succesfully\n";
	std::cout << "[!] attempting to fix directory table base (cr3)\n";

	if ( !memory::attach( ) )
		return -2;

	std::cout << "[+] memflow attached to fortnite succesfully\n";

	// bruteforce uworld (pasted from uc)
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

	while ( true ) {
		std::uintptr_t address{ };
		std::cout << "enter any address to read or -1 to exit: 0x";
		std::cin >> std::hex >> address;

		if ( address == -1 ) 
			break;

		std::uint64_t output = memory::read< std::uint64_t >( address );
		std::cout << std::hex << address << " = " << std::hex << output << '\n';
	}

	return 0;
}