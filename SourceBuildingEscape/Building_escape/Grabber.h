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

public:	// right now there is nothing we can do from the outside
	// Sets default values for this component's properties
	UGrabber(); //constructeur , class derived from uobject
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;



private: // private variable , member variable 
float Reach = 200.f;
void Grab();
void Release();
void FindPhysicHandle();
void SetupInputComponent();
// lesson 43 Uphysichanel
UPhysicsHandleComponent* PhysicsHandle =nullptr; // declaring variables here make them accessible by any function inside the Grabber.cpp
// we give it a null pointer in case the graber start ot exist before the physics handle starts, that could cause crashes
UInputComponent* InputComponent	=nullptr; // always initailinse null pointer to poitners !

//return an a Hitresult , first aactor within reach with physics body
FHitResult GetFirstPhysicsBodyInReach() const ; // conns means it wont change the value of the object 
// Return linetrace End
FVector GetPlayerReach()const; 
//Get Plyaer postion in the world
FVector GetPlayersWorldPos() const;
};
