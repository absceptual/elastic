#include <vector>
#include <thread>
#include <chrono>

#include "memory/memory.h"
#include "memory/offsets.hpp"
#include "engine/engine.hpp"
#include "cheat/aimbot.hpp"


#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

void setNonBlockingMode() {
    struct termios ttystate;
    // Get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    // Turn off canonical mode and echo
    ttystate.c_lflag &= ~(ICANON | ECHO);
    // Minimum of number input read.
    ttystate.c_cc[VMIN] = 1;

    // Set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    // Set non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);
}

void resetBlockingMode() {
    struct termios ttystate;
    // Get the terminal state
    tcgetattr(STDIN_FILENO, &ttystate);

    // Turn on canonical mode and echo
    ttystate.c_lflag |= (ICANON | ECHO);

    // Set the terminal attributes.
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    // Set blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK);
}

void aim_at( AController* controller, FVector location ) {
	const double magnitude = std::sqrt( std::pow( location.x, 2 ) + std::pow( location.y, 2 ) + std::pow( location.z, 2 ) );
	const auto delta = location - camera::location;

	double yaw = atan( delta.y / delta.x ) * ( 180 / std::numbers::pi );
	double pitch = acos( delta.z / magnitude ) * ( 180 / std::numbers::pi );

	if ( yaw >= 8388608.f || pitch >= 8388608.f )
		return;
}

int main( int argc, char *argv[ ] ) {

	setNonBlockingMode( );

	if ( !memory::init( ) ) 
		return -1;

	std::cout << "[+] memflow initalized succesfully\n";

	if ( !aimbot::init( ) )
		return -1;

	std::cout << "[+] aimbot module initalized succesfully\n";

	std::cout << aimbot::mouse->move( 20000, 400 ) << '\n';

	std::cout << "[!] attempting to fix directory table base (cr3)\n";

	aimbot::init( );
	
	if ( !memory::attach( ) )
		return -2;

	
	std::cout << "[+] memflow attached to fortnite succesfully\n";
	
	auto world = UWorld::GetUWorld( );
	std::cout << std::hex << world << '\n';
	
	
	std::vector< APlayerState* > actors{ };

	bool enabled = false;
	bool reset = false;
	auto controller = world->GetOwningGameInstance( )->GetLocalPlayer( )->GetPlayerController( );
	uintptr_t manager = memory::read< std::uintptr_t >( (uintptr_t)(controller) + 0x348 );
	while (true) {
		
		char c;
		if (read(STDIN_FILENO, &c, 1) > 0) {
            if ( c == '1' ) { 
				enabled = true;
			}
			else if ( c == '2' ) {
				enabled = false;
				reset = false;
			}
			else if ( c == '3' ) {
				break;
			}
        }

		if ( !enabled && !reset ) {
			reset = true;
			struct aimbot_angles {
				float a, b, c, d;
			} ang;

			ang.a = -89.9999f;
			ang.b = 89.9999f;
			ang.c = 0.0000f;
			ang.d = 359.9999f;
					// std::cout << camera::rotation << '\n';
			//std::cout << pitch << ", " << yaw << '\n';
			
			memory::write< aimbot_angles >( manager + 0x248c, ang );
		}


		std::cout << world->GetGameState( )->GetPlayerCount( ) << '\n';
		for ( int i = 0; i < world->GetGameState( )->GetPlayerCount( ); ++i ) {
			const auto state = world->GetGameState( )->GetPlayerState( i );
			const auto pawn = state->GetPawn( );
			if ( !pawn )
				continue;

			const auto team_index = memory::read< std::uint8_t >( (uintptr_t)(pawn) + offsets::team_index );
			//if ( team_index == memory::read< std::uint8_t >( (uintptr_t)( controller->GetPawn( ) + offsets::team_index ) ) )
				//1continue;

			if ( pawn == controller->GetPawn( ) )
				continue;

			actors.push_back( state );
		}

		float c_dist = __INT_MAX__;
		APlayerState* closest_pawn = nullptr;
		for ( const auto& state : actors ) {
			FVector target = state->GetPawn( )->GetMesh( )->GetBoneTransform( 110 );
			double distance = camera::location.distance( target );

			if ( distance < c_dist ) {
				c_dist = distance;
				closest_pawn = state;
			}
		}


		if ( enabled && closest_pawn && world->GetGameState( )->GetPlayerState( 0 )->GetPawn( ) ) {
			FVector head = closest_pawn->GetPawn( )->GetMesh( )->GetBoneTransform( 110 );
			camera::update( );

			std::cout << "skib?\n";
			
			const auto delta = head - camera::location;
			const auto hyp = sqrt( (delta.x * delta.x) + (delta.y * delta.y)  );	
			float pitch = RAD2DEG(atan2( delta.z, hyp ));
			float yaw = RAD2DEG(atan2( delta.y, delta.x));
		
			if ( pitch > 90 )
				pitch = 89;
			else if ( pitch < -90 )
				pitch = -89;

			if ( yaw > 180 )
				yaw = 179;
			else if ( yaw < -180 )
				yaw = -179;
			
			struct aimbot_angles {
				float a, b, c, d;
			} ang;

			ang.a = pitch;
			ang.b = pitch;
			ang.c = yaw;
			ang.d = yaw;
					// std::cout << camera::rotation << '\n';
			//std::cout << pitch << ", " << yaw << '\n';
			
			memory::write< aimbot_angles >( manager + 0x248c, ang );
			//memory::write< float >( manager + 0x248c, pitch);
			//memory::write< float >( manager + 0x2490, pitch);
			//memory::write< float >( manager + 0x2494, yaw);
			//memory::write< float >( manager + 0x2498, yaw );
			
			//FVector d{ pitch - camera::rotation.x, yaw - camera::rotation.y, 0};
			//std::cout << utils::world_to_screen( head ) << '\n';
			//std::cout << pitch << ", " << '\n';
			//std::cout << camera::rotation << "\n";
			//std::cout << d << '\n';
			//memory::write< FVector >( (uintptr_t)controller + 0x518 + 0x8, d );
		}
		else { 
			float ViewPitchMin = -89.9999f;
    		float ViewPitchMax = 89.9999f;
    		float ViewYawMin = 0.0000f;
    		float ViewYawMax = 359.9999f;

			memory::write< float >( manager + 0x248c, ViewPitchMin);
			memory::write< float >( manager + 0x2490, ViewPitchMax);
			memory::write< float >( manager + 0x2494, ViewYawMin);
			memory::write< float >( manager + 0x2498, ViewYawMax );
		}
		actors.clear( );
	}
	

	memory::detach( );
}