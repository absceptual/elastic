#include "memory.h"

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
	if ( os.process_by_name( "FortniteClient", &instance ) ) {
		std::cout << "[driver!find_process] failed to find Fortnite\n";
		return false;
	}
	
	ProcessInfo info{ };
    info.dtb2 = Address_INVALID;
	if ( os.process_info_by_name( "FortniteClient", &info ) )
        return false;
    
   	ModuleInfo module_info{ };
    if ( instance.module_by_name( "FortniteClient-Win64-Shipping.exe", &module_info ) )
	{
		for ( size_t dtb = 0; dtb <= SIZE_MAX; dtb += 0x1000 )
		{
			instance.set_dtb( dtb, Address_INVALID );
			os.process_by_info( info, &instance );

			if ( !instance.module_by_name( "FortniteClient-Win64-Shipping.exe", &module_info ) )		
				break;

			if ( dtb == SIZE_MAX )
                return false;

            instance.set_dtb(dtb, 0);
		}
    }

    os.clone().into_process_by_info(info, &process);
    base = module_info.base;

    return true;
}

ModuleInfo memory::get_module( std::string module_name ) {
    ModuleInfo info{ };
    if ( !base )
        return info;

    if ( instance.module_by_name( "FortniteClient-Win64-Shipping.exe", &info ) ) 
        attach( );
    
	instance.module_list_callback( NULL, [ & ]( ModuleInfo module_info ) {
        if ( module_name.compare( module_info.name ) ) 
            return true;
        
		std::cout << "[process:find_module] found module " << module_name << ": 0x" << std::hex << module_info.base << '\n';
        info = module_info;
		return false;
	} );

    return info;
}

