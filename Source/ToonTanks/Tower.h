// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

	// we need a tick function as we removed it from basepawn
	public:
	virtual void Tick(float DeltaTime) override;

	 void HandleDestruction();
    protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

	private:
	class ATank* Tank; // forward declare !
	UPROPERTY(VisibleAnywhere,BluePrintReadWrite, Category = "Components", meta= (AllowPrivateAccess = "true"))
	float FireRange=800.f;
	FTimerHandle FireRateTimeHandle;
	float FireRate= 2.f;
	void CheckFireCondition();

	bool InFireRange();

};
