#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "engine.hpp"

namespace camera {
    inline FVector rotation{ };
    inline FVector position{ };
    inline float fov{ };

    inline void update( ) {
        static auto world = UWorld::GetUWorld( );
        auto controller = world->GetOwningGameInstance( )->GetLocalPlayer( )->GetPlayerController( );
        
        // Rotation is stored in radians, let's convert it to degrees
        const auto rotation_pointer = memory::read< std::uintptr_t >( std::uintptr_t( world ) + offsets::world_camera_rotation );
        const auto location_pointer = memory::read< std::uintptr_t >( std::uintptr_t( world ) + offsets::world_camera_location );

        struct RotationInfo
		{
			double pitch;
			char pad_0008[24];
			double yaw;
			char pad_0028[424];
			double roll;
		} rotationInfo;

		rotationInfo.pitch = memory::read< double >(rotation_pointer);
		rotationInfo.yaw = memory::read<double>(rotation_pointer + 0x20);
		rotationInfo.roll = memory::read< double >(rotation_pointer + 0x1d0);

        camera::position = memory::read< FVector >(location_pointer);
		camera::rotation.x = asin(rotationInfo.roll) * (180.0 / std::numbers::pi);
		camera::rotation.y = ((atan2(rotationInfo.pitch * -1, rotationInfo.yaw) * (180.0 / std::numbers::pi)) * -1) * -1;
		camera::fov = memory::read<float>((uintptr_t)controller + 0x394) * 90.f;
    }
}
class AFortPawn : public ACharacter { 
    void GetCurrentWeapon( ) { };
    void GetCurrentWeaponList( ) { };
    void IsDead( ) { };
    void IsKnocked( ) { };
    void GetTeam( ) { };
};

class AFortPlayerPawn : public AFortPawn {
    void GetCurrentVehicle( ) { };
    void IsInVehicle( ) { };
    void IsDrivingVehicle( ) { };
    void IsSprinting( ) { };
    void IsGliding( ) { };
    void IsSkyDiving( ) { };
};

class AFortPlayerStateAthena : public AActor {
    void GetSeasonLevel( ) { };
    void GetKillScore( ) { };
};

class AFortPlayerState : public AFortPlayerStateAthena, APlayerState {
    void GetPlatform( ) { };
};

class AFortPlayerStateZone : public AFortPlayerState {
    void GetSpectatorCount( ) { };
};

class UFortItemDefinition : public UItemDefinitionBase {
    void GetRarity( ) { };
};

class UFortWeaponRangedItemDefinition : public UFortItemDefinition { 
    void HasLightweightProjectile( ) { };
};

class UFortWeaponItemDefinition : public UFortWeaponRangedItemDefinition { };
class FFortBaseWeaponStats : public UObject { };

class AFortWeapon : public AActor { 
    void GetProjectileGravity( );
    void GetProjectileSpeed( );
    void GetWeaponData( );
    void GetWeaponCoreAnimation( );
    void GetTargetingSourceLocation( ) { };
    void CanFire( ) { };
    void GetMuzzleLocation( ) { };
    void GetBulletsPerClip( ) { };
    void IsReloading( ) { };
    void GetMagazineAmmoCount( ) { };
    void GetRemainingAmmo( ) { };
};

class AFortWeaponRanged : public AFortWeapon { };

class UFortVehicleFuelComponent : public AActor {
    void SetServerFuel( ) { };
    void SetInfiniteFuel( ) { };
    void GetFuelCapacity( ) { };
};

class UFortPhysicsVehicleConfigs : public AActor {
    void SetDragCoefficient2( ) { };
};

class AFortAthenAVehicle : public AActor {
    void GetCachedFuelComponent( ) { };
    void GetVehicleConfigs( ) { };
    void GetHealth( ) { };
    void GetMaxHealth( ) { };
};

class UFortLocalPlayer : public ULocalPlayer {
    void GetViewportClient( ) { };
    void GetViewState( ) { };
};

class UFortKismetLibrary : public UObject {
    void GetPlayerAimPointHit( ) { };
    void CompareTeams( ) { };
};

#endif