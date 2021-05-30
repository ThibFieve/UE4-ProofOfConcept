// Copyright thibault Fievez 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber(); //constructeur , class derived from uobject

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private: // private variable , member variable 
float Reach = 100.f;
void Grab();
UPhysicsHandleComponent* PhysicsHandle =nullptr; // declaring variables here make them accessible by any function inside the Grabber.cpp
// we give it a null pointer in case the graber start ot exist before the physics handle starts, that could cause crashes
UInputComponent* InputComponent	=nullptr;



};
