#include "driver.h"

Driver::Driver( ) {
    mf_log_init(LevelFilter::LevelFilter_Info);
	inventory = mf_inventory_scan( );

	if ( !inventory ) {
		std::cout << "[driver::init] failed to find a memflow inventory!\n";
		std::exit(-1);
	}

	if ( !connection ) {
		std::cout << "[driver::init] failed to create a memflow connector!\n";
		std::exit(-1);
	}

	if ( mf_inventory_create_connector(inventory, "qemu", "", &connector ) ) {
		std::cout << "[driver::init] failed to initalize the inventory connector\n";
		mf_inventory_free(inventory);
		std::exit(-1);
	}

	if ( mf_inventory_create_os(inventory, "win32", "", connection, &os) ) {
		std::cout << "[driver::init] unable to initalize os plugin\n";
		std::exit(-1);
	}
	std::cout << "[driver::init] memflow connector initalized: " << std::hex << connector.container.instance.instance << "\n";
}

Process Driver::find_process(std::string process_name) {
	ProcessInstance<> target{ };
	if ( os.process_by_name(STR(process_name.c_str()), &target ) ) 
		std::cout << "[driver!find_process] failed to find process " << process_name << "\n";
	
	return Process(target);
	//const ProcessInfo* info{ target.info( ) };
	//printf("%s process found: 0x%lx] %d %s %s\n", process_name.c_str( ), info->address,
	//				 info->pid, info->name, info->path);


}