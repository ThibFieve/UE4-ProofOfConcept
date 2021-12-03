// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class MYSIMPLE_SHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	
	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere) // those will be pointer so we want them to be visible not editable
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh; // this is a skeletal mesh , not just a static mesh . for some reason , it should have been a static but that's how it is in teh assets pack

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere)
	UParticleSystem* Impact;

	UPROPERTY(EditAnywhere)
	float MaxRange=2000.f;

	UPROPERTY(EditAnywhere)
	float Damage=20.f;



	UPROPERTY(EditAnywhere)
	USoundBase* MuzzleSound;


	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;
	

	bool GunTrace(FHitResult& outHit, FVector& outShotDirection);

	AController* GetOwnerController() const;
};
