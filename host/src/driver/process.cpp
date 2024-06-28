#include "process.h"

Process::Process(std::shared_ptr<ProcessInstance<>> instance, OsInstance<>& os) : m_instance{ instance }, m_info{ m_instance.get()->info( ) } {  
    m_name = m_info->name;
    m_pid = m_info->pid;
    m_path = m_info->path;
    m_eprocess = m_info->address;
    ModuleInfo m{ };
    instance.get()->primary_module(&m);
   

    ProcessInfo info;
    info.dtb2 = Address_INVALID;

	if (os.process_info_by_name(STR(m_name.c_str()), &info))
	{
		exit(-3);
	}

    
   	ModuleInfo module_info;
    if (m_instance.get()->module_by_name(STR("FortniteClient-Win64-Shipping.exe"), &module_info))
	{
		printf("Can't find base module info for process %s. Trying with a new dtb...\n", m_name.c_str());

        ProcessInstance<>* tmp_proc = m_instance.get();
		for (size_t dtb = 0; dtb <= SIZE_MAX; dtb += 0x1000)
		{
			info.dtb1 = dtb;
			os.process_by_info(info, m_instance.get());

			if (!tmp_proc->module_by_name(STR("FortniteClient-Win64-Shipping.exe"), &module_info))		
				break;

			if (dtb == SIZE_MAX)
			{
				printf("Access error for process %s\n", m_name.c_str());
				exit(-3);
			}

            tmp_proc->set_dtb(dtb, 0);
		}
	}

    os.clone().into_process_by_info(info, &m_process);
    m_base = module_info.base;
    
    //cr3 = m_info->dtb1;
    //std::uint8_t buffer[1024]{ };
    
}

ModuleInfo Process::find_module(std::string module_name) {
    ModuleInfo info{ };
    if (m_instance.get()->module_by_name(STR("FortniteClient-Win64-Shipping.exe"), &info)) {
        std::cout << "setting (again!)\n";
        m_instance.get()->set_dtb(m_info->dtb1, 0);
    }

	m_instance.get()->module_list_callback(NULL, [&](ModuleInfo module_info){
        if (module_name.compare(module_info.name)) {
            return true;
        }

		std::cout << "[process:find_module] found module " << module_name << ": 0x" << std::hex << module_info.base << '\n';
        info = module_info;
		return false;
	});

    return info;
}


std::uintptr_t Process::get_base( ) {

    return m_base;
}

std::uintptr_t Process::get_eprocess( ) {
    return m_eprocess;
}

std::uint32_t Process::get_pid( ) {
    return m_pid;
}

std::string Process::get_name( ) {
    return m_name;
}

std::string Process::get_path( ) {
    return m_path;
}

const ProcessInfo* Process::get_info( ) {
    return m_info;
}
