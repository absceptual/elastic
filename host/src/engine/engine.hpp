#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "math.hpp"

#include "../memory/memory.h"
#include "../memory/offsets.hpp"


class UObject { };
class FName { };
class AInfo { };

class USceneComponent;
class APawn;
class ACharacter;
class USkeletalMeshComponent;

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
    USceneComponent* GetRootComponent( ) { };
    FVector GetVelocity( ) { };
    FVector GetActorLocation( ) { };
    void SetActorLocation( ) { };
    void GetActorRotation( ) { };
    void SetActorRotation( ) { };
};

class APlayerState : public UObject { 
public:
    APawn* GetPawn( ) {
        return memory::read< APawn* >( reinterpret_cast< uintptr_t >( this ) + offsets::pawn_private );
    };
    void GetPlayerName( ) { };
    void IsBot( ) { };
    void IsSpectator( ) { };
    std::int32_t GetTeamIndex( ) {
        return memory::read< std::int32_t >( reinterpret_cast< uintptr_t >( this ) + offsets::team_index );
    }
};

class AController : public AActor {
public:
    void GetPlayerState( ) { };
    void GetStateName( ) { };
    ACharacter* GetCharacter( ) { };
    void GetControlRotation( ) { };
    void GetPlayerViewPoint( ) { };
    void GetViewTarget( );
    APawn* GetPawn( ) { 
        return memory::read< APawn* >( reinterpret_cast< std::uintptr_t >( this ) + offsets::local_pawn );
    };
    void SetControlRotation( ) { };
};

class AAIController : public AController { };
class APlayerController : public AController {
public:
    void GetHitResultAtScreenPosition( ) { };
    void GetLocalPlayer( ) { };
    void GetPlatformUserId( ) { };
    void GetPlayerCameraManager( ) { };
    void GetPlayerInput( ) { };
    void GetYawScale( ) { };
    void GetPitchScale( ) { };
    void GetSpectatorPawn( ) { };
};

class APawn : public AActor {
public:
    // void GetController( ) { };
    //void GetControlRotation( ) { };
    APlayerState* GetPlayerState( ) { 
        return memory::read< APlayerState* >( reinterpret_cast< std::uintptr_t >( this ) + offsets::player_state );
    }
   // void GetViewRotation( ) { };
    USceneComponent* GetRootComponent( ) { 
        return memory::read< USceneComponent* >( reinterpret_cast< std::uintptr_t >( this ) + offsets::root_component );
    };

    USkeletalMeshComponent* GetMesh( ) {
        return memory::read< USkeletalMeshComponent* >( reinterpret_cast< std::uintptr_t >( this ) + offsets::mesh );
    }

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
public:
    APlayerState* GetPlayerState( int index ) { 
        auto state_array = memory::read< std::uintptr_t >( reinterpret_cast< std::uintptr_t >( this ) + offsets::player_array );
        return memory::read< APlayerState* >( state_array + ( index * sizeof( std::uintptr_t ) ) );
    };   

    std::int32_t GetPlayerCount( ) {
        auto state_array = memory::read< std::uintptr_t >( reinterpret_cast< std::uintptr_t >( this ) + offsets::player_array );
        return memory::read< std::int32_t >( reinterpret_cast< std::uintptr_t >( this ) + offsets::player_array + sizeof( std::uintptr_t ) );
    }
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
    APlayerController* GetPlayerController( ) { };
};

class ULocalPlayer : public UPlayer {
public:
    void GetGameInstance( ) { };
    void GetIndexInGameInstance( ) { };
    void GetNickname( ) { };
    void GetPlatformUserId( ) { };
    void GetViewpoint( ) { };
    void GetWorld( ) { };
    APlayerController* GetPlayerController( ) {
        return memory::read< APlayerController* >( (uintptr_t)this + offsets::player_controller );
    }
    void SetPlatformUserId( ) { };
};


class ULevel : public UObject {
    void GetWorldSettings( ) { };
    void GetActors( ) { };
};


class UGameInstance : public UObject {
public:
    ULocalPlayer* GetLocalPlayer( ) {
        return memory::read< ULocalPlayer* >( memory::read< std::uintptr_t >(
            reinterpret_cast< uintptr_t >( this ) + offsets::local_players
        ));
    }
};


class UWorld : public UObject {
public:
    static UWorld* GetUWorld( ) {
        static bool fixed = false;
        static std::uintptr_t va_text{ };
        if ( !fixed ) {
            for (int i = 0; i < 25; i++) {
                std::int32_t address{ };

                if ( memory::read< std::int32_t >( memory::base + ( i * 0x1000 ) + 0x250 ) == 0x260E020B ) 
                    va_text = memory::base + ( ( i + 1 ) * 0x1000 );
            }

            va_text += offsets::uworld;
        }
	   
        return memory::read< UWorld* >( va_text );
	}

    UGameInstance* GetOwningGameInstance( ) { 
        return memory::read< UGameInstance* >( reinterpret_cast< uintptr_t >( this ) + offsets::game_instance  );
    };

    ULevel* GetPersistentLevel( ) { 
        return memory::read< ULevel* >( reinterpret_cast< uintptr_t >( this ) + offsets::persistent_level  );
    };

    AGameState* GetGameState( ) { 
        return memory::read< AGameState* >( reinterpret_cast< uintptr_t >( this ) + offsets::game_state  );
    }
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
    FVector GetLocation( ) {
        return memory::read< FVector >( reinterpret_cast< std::uintptr_t >( this ) + offsets::relative_location );
    };

    FVector GetVelocity( ) {
        return memory::read< FVector >( reinterpret_cast< std::uintptr_t >( this ) + offsets::component_velocity );
    };

    FVector GetRotation( ) { 
        return memory::read< FVector >( reinterpret_cast< std::uintptr_t >( this ) + offsets::relative_rotation );
    };
};

class UMeshComponent : public USceneComponent {
    void GetMaterials( ) { };
};

class UStaticMeshComponent : public UMeshComponent {};
class USkinnedMeshComponent : public UStaticMeshComponent {
public:
    void GetBoneName( ) { };
    void GetBoneCount( ) { };
    FVector GetBoneTransform( std::int32_t id ) { 
        auto bone_array = memory::read< std::uintptr_t >( reinterpret_cast< std::uintptr_t >( this ) + offsets::bone_array );
        if ( !bone_array )
            bone_array = memory::read< std::uintptr_t >( reinterpret_cast< std::uintptr_t >( this ) + offsets::bone_array_cache );

        FTransform bone = memory::read< FTransform >( bone_array + ( id * 0x60 ) );
        FTransform component_to_world = memory::read< FTransform >( reinterpret_cast< std::uintptr_t >( this ) + offsets::component_to_world );

        FMatrix matrix = bone.to_matrix( ) * component_to_world.to_matrix( );
        return FVector( matrix._41, matrix._42, matrix._43 );
        
    };
};

class USkeletalMeshComponent : public USkinnedMeshComponent {
    void SetGlobalAnimationRateScale( ) { };
};

class UItemDefinitionBase : public UObject {
    void GetItemName( ) { };
};

#endif