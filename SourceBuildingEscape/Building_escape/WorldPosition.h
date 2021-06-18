// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WorldPosition.generated.h" // this generated file must be at the bottom of all the includes


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UWorldPosition : public UActorComponent
{//Worldcomponent is inherite from actor compoenent
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWorldPosition(); // basic setup constructor

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
