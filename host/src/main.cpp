#include "memory/memory.h"
#include <vector>

#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {

	/*
	Driver driver{ };
	auto process = driver.find_fortnite( );
	auto base = process.get_base();

	std::cout << std::hex << process.get_base() << '\n';
	std::cout << std::hex << process.m_info->dtb1 << '\n';
	std::uint64_t va_text = 0;
	for (int i = 0; i < 25; i++) {
		std::int32_t address{ };

		process.read<std::int32_t>(base + (i * 0x1000) + 0x250, address);
		if (address == 0x260E020B) {
			std::cout << "holy shit i love kids\n";
			va_text = base + ((i + 1) * 0x1000);
		}
	}

	std::uint64_t GWorld = 0x117105c8 + va_text;
	std::cout << va_text << " LOOOOOOOOOOOOOL\n";
	std::cout << GWorld << " LOOOOOOOOOOOOOL\n";

	std::uint64_t UWorld;
	process.read<std::uint64_t>(GWorld, UWorld);	

	while (true) {
		std::uint64_t address;
		std::cin >> std::hex >> address;

		if (address == -1) {
			break;
		}

		std::uint64_t output{ };
		process.read<std::uint64_t>(address, output);
		std::cout << std::hex << output << '\n';
	}

	/*
	std::cout << UWorld << '\n';
	
	std::uint64_t GameInstance{ };
	process.read<std::uint64_t>(UWorld + 0x1d8, GameInstance);

		std::cout << GameInstance << '\n';

	std::uint64_t LocalPlayers{ };
	process.read<std::uint64_t>(GameInstance + 0x38, LocalPlayers);

	std::cout << LocalPlayers << '\n';

	std::uint64_t PlayerController { };
	process.read<std::uint64_t>(LocalPlayers + 0x30, PlayerController);

	std::cout << PlayerController << '\n';

	std::uint64_t LocalPawn { };
	process.read<std::uint64_t>(PlayerController + 0x338, LocalPawn);

	std::cout << "?: " << LocalPawn << '\n';
	
	std::uint64_t PlayerWeapon { };
	process.read<std::uint64_t>(LocalPawn + 0xA68, PlayerWeapon);

	std::uint64_t AmmoCount { };
	process.read<std::uint64_t>(PlayerWeapon + 0xEEC, AmmoCount);

	std::cout << AmmoCount << '\n';
	std::cout << "i love xeb!\n";
	*/
	
	return 0;
}