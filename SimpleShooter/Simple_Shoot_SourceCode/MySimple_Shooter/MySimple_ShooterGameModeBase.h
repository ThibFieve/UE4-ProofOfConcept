// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MySimple_ShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYSIMPLE_SHOOTER_API AMySimple_ShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
	virtual void PawnKilled(APawn* PawnKilled);
};
