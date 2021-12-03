// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_ClearBackboardValue.generated.h"

/**
 * 
 */
UCLASS()
class MYSIMPLE_SHOOTER_API UBTTask_ClearBackboardValue : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	public:
	UBTTask_ClearBackboardValue(); // constructor

	protected :

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
