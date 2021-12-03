// Fill out your copyright notice in the Description page of Project Settings.

#pragma once // this is to protect including amny times the same header file

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// For learning purposes/////////////////////////////
	UPROPERTY(VisibleAnywhere,BluePrintReadWrite) // Blueprint Read write is to allow to use it in event graph of blueprints
	int32 VisibleAnywhereInt=12;

	UPROPERTY(EditAnywhere, BluePrintReadOnly)
	int32 EditAnywhereInt=22;

	UPROPERTY(VisibleInstanceOnly) // only instance can see 
	int32 VisibleInstanceOnlyInt=11;

	UPROPERTY(VisibleDefaultsOnly)
	int32 VisibleDefaultsOnlyInt=5;

	UPROPERTY(EditDefaultsOnly)
	int32 EditDefaultOnlyInt = 9;
	UPROPERTY(EditInstanceOnly)
	int32 EditInstanceOnlyInt = 12;

	UPROPERTY(EditAnywhere)
	float Speed = 400.f;
	//////////////////////////////////////////////////////

    void HandleDestruction();

protected: // Protected , only child class can access

    void RotateTurret(FVector LookAtTarget);

	void Fire();

private: // member variables should be private so they only can be acesses by the class that owns them !
//capsule
	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true")) // this is a unreal engine marco that makes the engine aware of the capsule for the reflection system , EXPOSE THIS VARIABLE TO BLUEPRINTS ! and garbage collection
	// by default the compiler doesnt know what a capsule component is , add an header file , but adding the whole header file just for that is not efficient, we could use forward declaration instead
	//
	class UCapsuleComponent* CapsuleComp; //we telling the compiler that this is a (incomplete) type if we treid to access its variable we would get an error, we would need the header file with definition
	//in basepawn.cpp , the program needs to know how big is a caspsule component in memory so it needs the header declaration of it , ine basepawn.h it is not required
	//  it is good practice to not bloat the header file , and do forward declare.
//SEE slides, include only what you use in .cpp , include as little as possible in .h file , dont need the header to delcare a pointer, bu do need the head to constrcut an object, acess member , inheritance
	
	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh; // dont need to forward deaclre as static mesh is included by default in actor, therefore base pawn	

	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh; 

	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint; 

	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Super Duper Variable", meta= (AllowPrivateAccess = "true")) // expose those varaible to the event graph even though they are private ! theya re still private but accessible from blueprints 
	int32 VisibleAnywherePrivateInt=12; // other classses still cannot access the private variable

	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Super Duper Variable", meta= (AllowPrivateAccess = "true")) // category allows to put them in certain category in the bluepriont UI
	int32 EditAnywherePrivateInt=22;



	UPROPERTY(EditDefaultsOnly,Category="Combat")
	TSubclassOf<class AProjectileClass> ProjectileClass; // forward declare Aprojectile class
	// this allows us to acess specific bluebprints from a cpp class
	// it allows us the pick a specific class that is either PorjectileClass or a subtype of projectile class
	// information exchanges between cpp and bluepritns is called reflection 

	

	UPROPERTY(EditAnywhere,Category="Combat")
class UParticleSystem* DeathParticles;

UPROPERTY(EditAnywhere,Category="Combat")
class USoundBase* DeathSound;

UPROPERTY(EditAnywhere,Category="Combat")
TSubclassOf<class UMatineeCameraShake> DeathCameraShakeClass;

	
};
