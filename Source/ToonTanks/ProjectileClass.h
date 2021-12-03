// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileClass.generated.h"

UCLASS()
class TOONTANKS_API AProjectileClass : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectileClass();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh; // for the base mesh of the projectile

UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Movement", meta= (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* MovementComponent; //here again we forward declare ! we add a component to our root base obejct that actually deals with movmenet
	UPROPERTY(EditAnywhere)
	float Damage=50.f;

//  MULTICAST DELEGATE /////////////////////////////////////////////////////
UFUNCTION()
void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit); // See lesson 157 , this is teh function used in a callback for OnComponentHit that is  MULTICAST DELEGATE , 
//it's a variable, a structure that has mutliple funtion and an invocation list (list of function to call) , when something happens it Broadcast and all bound functions are called !.
 

//  END  MULTICAST DELEGATE /////////////////////////////////////////////////////


// PARTICLE SYSTEM//////////////////////
UPROPERTY(EditAnywhere,Category="Combat")
class UParticleSystem* HitParticles;

UPROPERTY(VisibleAnywhere,Category="Combat")
class UParticleSystemComponent* TrailParticles;

UPROPERTY(EditAnywhere,Category="Combat")
class USoundBase* LaunchSound;
UPROPERTY(EditAnywhere,Category="Combat")
class USoundBase* HitSound;

UPROPERTY(EditAnywhere,Category="Combat")
TSubclassOf<class UMatineeCameraShake> HitCameraShakeClass;

};
