#include "driver/driver.h"
#include <vector>

#include <thread>
#include <chrono>

int main(int argc, char *argv[]) {
	Driver driver{ };
	auto process = driver.find_fortnite( );

	std::cout << std::hex << process.get_base() << '\n';

	//std::uint64_t cached_pml4e[512]{ };

	//std::uint8_t buffer{ };
    //CSliceMut<uint8_t> header{(char*)&buffer, sizeof(std::uint8_t)};

	//auto cr3 = process.m_info->dtb1;
	//auto phys_view = driver.connection->phys_view();
	for (int i = 0; i < 120; ++i) {
		// phys_view.read_raw_into(cr3, header);
		// process.m_instance.get()->set_dtb(cr3, 0);
		std::this_thread::sleep_for(std::chrono::seconds(1));
		std::cout << process.find_module("ntdll.dll").name << '\n';
	}
	

	std::cout << process.find_module("ntdll.dll").name << '\n';
	std::cout << process.get_base() << '\n';
	return 0;
}