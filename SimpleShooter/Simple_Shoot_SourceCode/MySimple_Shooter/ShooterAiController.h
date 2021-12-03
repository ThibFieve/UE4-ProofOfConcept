// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAiController.generated.h"

/**
 * 
 */
UCLASS()
class MYSIMPLE_SHOOTER_API AShooterAiController : public AAIController
{
	GENERATED_BODY()


	//Begin play is a protected function
	public:
	virtual void Tick(float DeltaTime) override;

	bool IsDead() const;

	protected:
	virtual void BeginPlay() override;
	
	private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius=200;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehavior; // forward declaration

	
};
