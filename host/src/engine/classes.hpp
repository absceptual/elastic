#ifndef CLASSES_HPP
#define CLASSES_HPP

#include "engine.hpp"

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