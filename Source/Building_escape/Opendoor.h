// Copyright thibault Fievez 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"

#include "Opendoor.generated.h"// this always needs to be at bottom


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpendoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpendoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
private:
float InitialYaw;
float CurrentYaw; // why declaring here , would they not be shared amongst instances then ?
UPROPERTY(EditAnywhere)// expose  something as parameter in the editorm if you click on object qnd then opendoor it zill be q vqriqble
float TargetYaw = 90.f ; // it is set to 90.f per default
	
UPROPERTY(EditAnywhere)
ATriggerVolume* PressurePlate; //it's a pointer !!! opens a menu in unreal that lets us pick any aAtriggervolume from the world and PressurePlate will be the pointer of that object
//warning , if we dont give a pressure plate component to the door it will crash , it will try to dereference in the code that we use a null pointer
// to use that pressure plate we can use function to decide what can trigger it IsOverlappingActor , it is  a polling method , the other way is using event . Polling the plates
// check peridiodically whereas event the object ells the plate 

UPROPERTY(EditAnywhere)
AActor* ActorThatOpen;


float DoorLastOpened =0.f;
UPROPERTY(EditAnywhere)
float DoorCloseDelay=1.f;

UPROPERTY(EditAnywhere)
float DoorOpenSpeed=0.8f;
UPROPERTY(EditAnywhere)
float DoorCloseSpeed=2.f;

};
