#include "driver/driver.h"
#include "driver/process.h"

int main(int argc, char *argv[]) {
	Driver driver{ };
	auto process = driver.find_process("notepad.exe");
	process.find_module("notepad.exe");
	return 0;
}