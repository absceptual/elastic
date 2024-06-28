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

	if ( mf_inventory_create_connector( inventory, "qemu", "", &connector ) ) {
		std::cout << "[driver::init] failed to initalize the inventory connector\n";
		mf_inventory_free( inventory );
		std::exit( -1 );
	}

	if ( mf_inventory_create_os( inventory, "win32", "", connection, &os ) ) {
		std::cout << "[driver::init] unable to initalize os plugin\n";
		std::exit( -1 );
	}
	
	std::cout << "[driver::init] memflow connector initalized: " << std::hex << connector.container.instance.instance << "\n";
}


Process Driver::find_fortnite(  ) {

	auto target = std::make_shared< ProcessInstance< > >( );
	if ( os.process_by_name( STR( "FortniteClient" ), target.get( ) ) ) {
		std::cout << "[driver!find_process] failed to find FortniteClient\n";
		target.reset( );
		std::exit(-1);
	}
	
	std::cout << "[driver!find_process] found FortniteClient!\n";
	std::cout << std::dec << target.get()->info()->pid << '\n';
	return Process( target, os );
}

OsInstance<> Driver::get_os() {
	return os;
}