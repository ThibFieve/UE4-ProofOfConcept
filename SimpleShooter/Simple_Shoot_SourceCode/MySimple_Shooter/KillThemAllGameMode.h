// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MySimple_ShooterGameModeBase.h"
#include "KillThemAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYSIMPLE_SHOOTER_API AKillThemAllGameMode : public AMySimple_ShooterGameModeBase
{
	GENERATED_BODY()
	public:
	virtual void PawnKilled(APawn* PawnKilled)override;
	private:
	void EndGame(bool bIsPlayerWinner);
};
