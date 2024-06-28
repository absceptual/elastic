#include "process.h"

Process::Process(ProcessInstance<> instance) : m_instance{ instance } { };

void Process::find_module(std::string module_name) {
    ModuleInfo* module_info{ };
	target.module_list_callback(NULL, [](ModuleInfo module_info){
        if (module_name.compare(module_info.name))
            return true;

		std::cout << "[driver::find_process] found module " << module_name << ": 0x" << std::hex << module_info.base << '\n';
		return false;
	});
}