#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "math.hpp"

#include "../memory/memory.h"


class UObject { };
class FName { };
class AInfo { };

class USceneComponent;
class APawn;
class ACharacter;

template <typename T>
class TArray {
    void operator[ ]( int i ) { };
    void GetSize( ) { };
    void IsValidIndex( ) { };
    void IsValid( ) { };
    void Add( ) { };
    void Remove( ) { };
    void New( ) { };
};

class FString : public TArray< wchar_t > { 
    void ToString( ) { };
    void c_str( ) { };
    void Length( ) { };
};

class AActor : public UObject { 
public:
    USceneComponent* GetRootComponent( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\x48\x8B\x81\xCC\xCC\xCC\xCC\x48\x85\xC0", "x", 3 )

        return memory::read< USceneComponent* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };

    FVector GetVelocity( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< FVector >( reinterpret_cast< uintptr_t >( this + offset ) );
    };

    FVector GetActorLocation( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< FVector >( reinterpret_cast< uintptr_t >( this + offset ) );
    };
    void SetActorLocation( ) { };
    void GetActorRotation( ) { };
    void SetActorRotation( ) { };
};

class APlayerState : public UObject { 
    void GetPawn( ) { };
    void GetPlayerName( ) { };
    void IsBot( ) { };
    void IsSpectator( ) { };
};

class AController : public UObject {
public:
    void GetPlayerState( ) { };
    void GetStateName( ) { };
    ACharacter* GetCharacter( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< ACharacter* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };
    void GetControlRotation( ) { };
    void GetPlayerViewPoint( ) { };
    void GetViewTarget( );
    APawn* GetPawn( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< APawn* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };
    void SetControlRotation( ) { };
};

class AAIController : public AController { };
class APlayerController : public AController {
public:
    void GetHitResultAtScreenPosition( ) { };
    void GetLocalPlayer( ) { };
    void GetPlatformUserId( ) { };
    void GetPlayer( ) { };
    void GetPlayerCameraManager( ) { };
    void GetPlayerInput( ) { };
    void GetYawScale( ) { };
    void GetPitchScale( ) { };
    void GetSpectatorPawn( ) { };
};

class APawn : public AActor {
    void GetController( ) { };
    void GetControlRotation( ) { };
    void GetPlayerState( ) { }
    void GetViewRotation( ) { };
    void GetRootComponent( ) { };
};

class ACharacter : public APawn {
    void GetMesh( ) { };
};



class AGameModeBase : public AInfo {
    void GetGameState( ) { }; 
    void GetSpectatorCount( ) { };
};

class AGameMode : public AGameModeBase {
    void GetMatchState( ) { };
    void GetHumanPlayerCount( ) { };
    void GetSpectatorCount( ) { };   
};


class AGameStateBase : public AInfo {
    void GetPlayerStates( ) { };   
};

class AGameState : public AGameStateBase {
    void GetMatchState( ) { };
};

class AWorldSettings : public AInfo {
    void GetGravity( ) { };
    void GetWorldGravity( ) { };
};

class APlayerCameraManager : public UObject {
    void GetFOVAngle( ) { };
    void GetCameraLocation( ) { };
    void GetCameraRotation( ) { };
};

class UPlayer : public UObject {
public:
    APlayerController* GetPlayerController( ) {
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< APlayerController* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };
};

class ULocalPlayer : public UPlayer {
public:
    void GetGameInstance( ) { };
    void GetIndexInGameInstance( ) { };
    void GetNickname( ) { };
    void GetPlatformUserId( ) { };
    void GetViewpoint( ) { };
    void GetWorld( ) { };
    void SetPlatformUserId( ) { };
};


class ULevel : public UObject {
    void GetWorldSettings( ) { };
    void GetActors( ) { };
};


class UGameInstance : public UObject {
public:
    ULocalPlayer* GetLocalPlayer( ) {
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< ULocalPlayer* >( reinterpret_cast< uintptr_t >( this + offset ) );
    }
};


class UWorld : public UObject {
public:

    void GetAuthorityGameMode( ) { };
    UGameInstance* GetOwningGameInstance( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< UGameInstance* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };

    void GetCameraLocation( ) { };
    void GetCameraRotation( ) { };
    ULevel* GetPersistentLevel( ) { 
        static std::size_t offset{ };
        SIG_SCAN( module::base, offset, "\xFF", "x", 0 )

        return memory::read< ULevel* >( reinterpret_cast< uintptr_t >( this + offset ) );
    };
    void GetLevels( ) { };
};


class UGameViewportClient : public UObject { 
    void Traceline( ) { };
    void GetUWorld( ) { };
};

class USceneViewState : public UObject {
    void GetProjection( ) { };
};

class UPrimitiveCompoenent { };
class USceneComponent : public UPrimitiveCompoenent { 
    void GetForwardVector( ) { };
    void GetComponentLocation( ) { };
};

class UMeshComponent : public USceneComponent {
    void GetMaterials( ) { };
};

class UStaticMeshComponent : public UMeshComponent {};
class USkinnedMeshComponent : public UStaticMeshComponent {
    void GetBoneName( ) { };
    void GetBoneCount( ) { };
};

class USkeletalMeshComponent : public USkinnedMeshComponent {
    void GetBoneLocation( ) { };
    void SetGlobalAnimationRateScale( ) { };
};

class UItemDefinitionBase : public UObject {
    void GetItemName( ) { };
};

#endif