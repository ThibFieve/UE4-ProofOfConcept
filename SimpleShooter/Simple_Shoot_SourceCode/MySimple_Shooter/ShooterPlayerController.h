// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MYSIMPLE_SHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	protected:
	virtual void BeginPlay() override;
	private:


	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass; // forward declare UUserWidget
	UPROPERTY() // this is to be sure that it is garbaged collected 
	UUserWidget* HUD;
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass; // forward declare UUserWidget

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass; // forward declare UUserWidget
	UPROPERTY(EditAnywhere)
	float RestartDelay=5.0f ;

	FTimerHandle RestartTimer;
};
