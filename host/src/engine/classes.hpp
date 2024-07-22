#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "engine.hpp"

namespace camera {
    // inline FMatrix projection_matrix;
    inline FVector location;
    inline FVector rotation;
    inline float fov;

    inline void update( ) {
        auto player = UWorld::GetUWorld( )->GetOwningGameInstance( )->GetLocalPlayer( );
        auto viewstates = memory::read< std::uintptr_t >( std::uintptr_t( player) + 0xD0 );
	    auto view_matrixes = memory::read< std::uintptr_t >( std::uintptr_t( viewstates ) + 0x8 );
        auto projection_matrix = memory::read< FMatrix >( view_matrixes + 0x900 );

        location = FVector( projection_matrix.m[3][0],  projection_matrix.m[3][1], projection_matrix.m[3][2] );
        rotation.x = RAD2DEG(asinf(projection_matrix.m[2][2]));
        rotation.y = RAD2DEG(atan2f(projection_matrix.m[2][1], projection_matrix.m[2][0]));
        rotation.z = RAD2DEG(atan2f(projection_matrix.m[0][2], projection_matrix.m[2][0]));

        float fov = atanf(1 / memory::read< double >(view_matrixes + 0x700)) * 2;
        camera::fov = RAD2DEG(fov);

        
        if ( rotation.y >= 90.f || rotation.y <= 90.f ) 
            camera::fov *= -1;

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