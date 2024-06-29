#include "memory.h"

// Initalize memflow and its required plugins for memory read and write
bool memory::init( ) {
    log_init( LevelFilter::LevelFilter_Info );
	inventory = inventory_scan( );

	if ( !inventory ) {
		std::cout << "[driver::init] failed to find a memflow inventory!\n";
		return false;
	}

	if ( !connection ) {
		std::cout << "[driver::init] failed to create a memflow connector!\n";
		return false;
	}

	if ( inventory_create_connector( inventory, "qemu", "", &connector ) ) {
		std::cout << "[driver::init] failed to initalize the inventory connector\n";
		inventory_free( inventory );
		return false;
	}

	if ( inventory_create_os( inventory, "win32", "", connection, &os ) ) {
		std::cout << "[driver::init] unable to initalize os plugin\n";
		return false;
	}

    return true;
}

bool memory::attach( ) {

    // Is fortnite running on the machine right now?
	if ( os.process_by_name( STR( "FortniteClient" ), &instance ) ) {
		std::cout << "[driver!find_process] failed to find Fortnite\n";
		return false;
	}
	
	ProcessInfo info{ };
    info.dtb2 = Address_INVALID;

    // Something went wrong if Fortnite is running but we cant retrieve the process information.
	if ( os.process_info_by_name( STR( "FortniteClient" ), &info ) )
        return false;
    
    // Start looking for the true directory table base if we can't find the module base of Fortnite
   	ModuleInfo module_info{ };
    if ( instance.module_by_name( STR( "FortniteClient-Win64-Shipping.exe" ), &module_info ) )
	{
        // Bruteforce the DTB going page by page
        // Try setting the DTB to the page we are currently on and see 
		for ( size_t dtb = 0; dtb <= SIZE_MAX; dtb += 0x1000 )
		{
			info.dtb1 = dtb;
			os.process_by_info( info, &instance );

			if ( !instance.module_by_name( STR( "FortniteClient-Win64-Shipping.exe" ), &module_info ) )		
				break;

			if ( dtb == SIZE_MAX )
                return false;

            instance.set_dtb(dtb, 0);
		}
    }

	// Create a process with the new DTB we found
    os.clone().into_process_by_info(info, &process);
    base = module_info.base;

    return true;
}

ModuleInfo memory::get_module( std::string module_name ) {
	// Don't look for a module if the memory module has not been initialized.
    ModuleInfo info{ };
    if ( !base )
        return info;

	// Did the CR3 change by chance?
    if ( instance.module_by_name( "FortniteClient-Win64-Shipping.exe", &info ) ) 
        attach( );
    
	// Loop through until we find a matchmaking
	instance.module_list_callback( NULL, [ & ]( ModuleInfo module_info ) {
        if ( module_name.compare( module_info.name ) ) 
            return true;
        
		std::cout << "[process:find_module] found module " << module_name << ": 0x" << std::hex << module_info.base << '\n';
        info = module_info;
		return false;
	} );

    return info;
}

