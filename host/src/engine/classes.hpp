#ifndef CLASSES_HPP
#define CLASSES_HPP

class UObject { };
class FName { };


class AActor : public UObject { 
   void GetRootComponent( ) {  };
   void GetTags( ) { };
   void GetVelocity( ) { };
   void GetActorLocation( ) { };
   void SetActorLocation( ) { };
   void GetActorRotation( ) { };
   void SetActorRotation( ) { };
};

class APlayerState : public UObject { 
    void GetPawn( ) { };
    void GetPlayerName( ) { };
    void IsBot( ) { };
    void IsSpectator( ) { };
}

class AController : public UObject {
    void GetPlayerState( ) { };
    void GetStateName( ) { };
    void GetCharacter( ) { };
    void GetControlRotation( ) { };
    void GetPawn( ) { };
    void GetPlayerViewPoint( ) { };
    void GetViewTarget( );
    void GetControlledPawn( ) { };
    void SetControlRotation( ) { };
}

class APawn : public AActor {
    void GetController( ) { };
    void GetControlRotation( ) { };
    void GetPlayerState( ) { }
    void GetViewRotation( ) { };
    void GetRootComponent( ) { };
}  

class ACharacter : public APawn {
    void GetMesh( ) { };
}

class AFortPawn : public ACharacter { 
    void GetCurrentWeapon( );
    void GetCurrentWeaponList( ) { };
    void IsDead( ) { };
    void IsKnocked( ) { };
    void GetTeam( ) { };
}

class AFortPlayerPawn : public AFortPawn {
    void GetCurrentVehicle( ) { };
    void IsInVehicle( ) { };
    void IsDrivingVehicle( ) { };
    void IsSprinting( ) { };
    void IsGliding( ) { };
    void IsSkyDiving( ) { };
}

class AController { };

class APlayerController : public AController {
    void GetHitResultAtScreenPosition( ) { };
    void GetLocalPlayer( ) { };
    void GetPlatformUserId( ) { };
    void GetPlayer( ) { };
    void GetPlayerCameraManager( ) { };
    void GetPlayerInput( ) { };
    void GetYawScale( ) { };
    void GetPitchScale( ) { };
    void GetSpectatorPawn( ) { }
};

class AAIController : public AController { };

class AInfo { };
class AGameModeBase : public AInfo {
    void GetGameState( ) { }; 
    void GetSpectatorCount( ) { };
} 

class AGameMode : public AGameModeBase {
    void GetMatchState( ) { };
    void GetHumanPlayerCount( ) { };
    void GetSpectatorCount( ) { };   
};

class AGameStateBase : public AInfo {
    void GetPlayerStates( ) { };   
}

class AGameState : public AGameStateBase {
    void GetMatchState( ) { };
};

class AWorldSettings : public AInfo {
    void GetGravity( ) { };
    void GetWorldGravity( ) { };
}

class APlayerCameraManager : public UObject {
    void GetFOVAngle( ) { };
    void GetCameraLocation( ) { };
    void GetCameraRotation( ) { };
}

class AFortPlayerStateAthena : public AActor {
    void GetSeasonLevel( ) { };
    void GetKillScore( ) { };
}

class AFortPlayerState : public AFortPlayerStateAthena, APlayerState {
    void GetPlatform( ) { };
}

class AFortPlayerStateZone : public AFortPlayerState {
    void GetSpectatorCount( ) { };
}

class UPrimitiveCompoenent { };

class USceneComponent : public UPrimitiveCompoenent { 
    void GetForwardVector( ) { };
    void GetComponentLocation( ) { };
}

class UMeshComponent : public USceneComponent {
    void GetMaterials( ) { };
}

class UStaticMeshComponent : public UMeshComponent {}

class USkinnedMeshComponent : public UStaticMeshComponent {
    void GetBoneName( ) { };
    void GetBoneCount( ) { };
}

class USkeletalMeshComponent : public USkinnedMeshComponent {
    void GetBoneLocation( ) { };
    void SetGlobalAnimationRateScale( ) { };
};

class UItemDefinitionBase : public UObject {
    void GetItemName( ) { };
}

class UFortItemDefinition : public UItemDefinitionBase {
    void GetRarity( ) { };
}

class UFortWeaponRangedItemDefinition : public UFortItemDefinition { 
    void HasLightweightProjectile( ) { };
}

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

class UFortVehicleFuelComponent : public AACtor {
    void SetServerFuel( ) { };
    void SetInfiniteFuel( ) { };
    void GetFuelCapacity( ) { };
}

class UFortPhysicsVehicleConfigs : public AActor {
    void SetDragCoefficient2( ) { };
}

class AFortAthenAVehicle : public AACtor {
    void GetCachedFuelComponent( ) { };
    void GetVehicleConfigs( ) { };
    void GetHealth( ) { };
    void GetMaxHealth( ) { };
}

class UGameViewportClient : public UObject { 
    void Traceline( ) { };
    void GetUWorld( ) { };
}

class UPlayer : public UObject {
    void GetPlayerController( ) { };
}

class USceneViewState : public UObject {
    void GetProjection( ) { };
}

class ULocalPlayer : public UFortLocalPlayer {
    void GetViewportClient( ) { };
    void GetViewState( ) { };
}

class UGameInstance : public UObject {
    void GetLocalPlayers( ) { };
}

class UFortKismetLibrary : public UObject {
    void GetPlayerAimPointHit( ) { };
    void CompareTeams( ) { };
}

class ULevel : public UObject {
    void GetWorldSettings( ) { };
    void GetActors( ) { };
    
}

class UWorld : public UObject {
    void GetAuthorityGameMode( ) { };
    void GetOwningGameInstance( ) { };
    void GetCameraLocation( ) { };
    void GetCameraRotation( ) { };
    void GetPersistentLevel( ) { };
    void GetLevels( ) { };

}

template <typename T>
class TArray {
    void operator[ ]( int i ) { };
    void GetSize( ) { };
    void IsValidIndex( ) { };
    void IsValid( ) { };
    void Add( ) { };
    void Remove( ) { };
    void New( ) { };
}

class FString : public TArray< wchar_t > { 
    void operator( ) { };
    void ToString( ) { };
    void c_str( ) { };
    void Length( ) { };
};


#endif