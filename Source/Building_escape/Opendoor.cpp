// Copyright thibault Fievez 2020
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"					// We do a top down approch from the world we find the player controller and then pawn to set it qs qctor thqt opens
#include "GameFramework/PlayerController.h" //
#include "Components/AudioComponent.h"

#include "GameFramework/Actor.h"
#include "Opendoor.h"

// Sets default values for this component's properties
UOpendoor::UOpendoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpendoor::BeginPlay()
{
	Super::BeginPlay();

	float MyFloat = 90.0f; // can aslo wrtie 90 engine will convert it , implicit convertion
	//FRotator CurrentRotation = GetOwner()-> GetActorRotation();// gives us a f rotator, gives  <y,Z,x rotation
	// ...
	// now we can do CurrentRotation.yaw

	//CurrentRotation.Yaw = 90.f ;

	//FRotator OpenDoor = {0.f,90.f,0.f}; // can also do FRotator Opendoor (0.f,90.f,0.f)

	//GetOwner() -> SetActorRotation(CurrentRotation) ;

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;
	TargetYaw = InitialYaw + TargetYaw;
	// could write TargetYaw += Initialyaw

	FindPressurePlate();

	//This line is not used anymore
	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn(); // getwolrd gives a pointer ; first player is a pointer , getpaw gives a pawn wgucg is a child of actor so it will work
	// the actor is also a pointer actaully so we can get even moe propertis from it

	//Audio
	FindAudioComponent();
}

void UOpendoor::FindPressurePlate()
{
	if (!PressurePlate)
	{
		// we cna do a warning /error log for any object that dont have a pressure plate
		UE_LOG(LogTemp, Error, TEXT(" No pressure plate for %s, watch out null pointer "), *GetOwner()->GetName());
	}
}

// Called every frame
void UOpendoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction); // Delta time is the time unreal takes to make a frame
	if (TotalMassOfActors() > MassToOpenDoor)
	//if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpen))//lazy evaluation ; if one of the condition is false it won't evaluate the rest , we can use to mitigate the crash issue
	{ // problem is this is cehcekd every frame
		// this is where we can have an issue if we dont set  a pressure plate we will have a null pointer for something that is a default compoenent , and unreal will crash
		// unreal will try to deference a null pointer
		OpenDoor(DeltaTime);
		// DoorLastOpened = when the door was opened
		DoorLastOpened = GetWorld()->GetTimeSeconds(); // times in second since the game is playing ,updated everyframe
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - DoorLastOpened > DoorCloseDelay)
		{

			//if door has been open longer than x seconds
			CloseDoor(DeltaTime);
		}
	}

	GetWorld()->GetTimeSeconds(); // times in second since the game is playing
}

void UOpendoor::OpenDoor(float DeltaTime)
{

	UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is %f"), GetOwner()->GetActorRotation().Yaw); // the star operation here is nto needed because not put into a string
	// ...

	//Set actor rotation

	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * DoorOpenSpeed); // to solve our issue we could multiply 0.0f by delta time and no more frame independat , tho Detltatime is really small
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	CloseDoorSound=false;
	if (!AudioComponent)
	{
		return;
	}
	if (!OpenDoorSound)
	{
		AudioComponent->Play(); // this plays at every frame , problem
		OpenDoorSound = true;
	}

	// WITH THE FOLLOWING THE DOOR GOES TO 90 no matter inital orientation

	/*
	float CurrentYaw= GetOwner()->GetActorRotation().Yaw;
	FRotator OpenDoor(0.f,0.f,0.f);
	OpenDoor.Yaw=FMath::Lerp(CurrentYaw,TargetYaw,0.01f) ;
	GetOwner() -> SetActorRotation(OpenDoor) ; // needs a rotator
*/

	// here we actually doing exponetial because we fed currentyaw,
	// could use FMath::FInterConstantTo() , this is also framerate in dependant
	// OpenDoor.Yaw=FMath::FInterpConstantTo(CurrentYaw,TargetYaw,DeltaTime,45) ; 45° per second. There is no easing to , its linear interpolation, will look unatural
	// OpenDoor.Yaw=FMath::FInterpTo(CurrentYaw,TargetYaw,DeltaTime,45) ; makes it framrate independant, delta time time needed by unreal to create a frame

	// That last line is the best way to do this

	// more explanation delta time lesson 26 , its the time between frames to be rendered
}

void UOpendoor::CloseDoor(float DeltaTime)
{

	//Set actor rotation

	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * DoorCloseSpeed); // to solve our issue we could multiply 0.0f by delta time and no more frame independat , tho Detltatime is really small
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
	OpenDoorSound=false;
	if (!AudioComponent)
	{
		return;
	}
	if (!CloseDoorSound)
	{
		AudioComponent->Play(); // this plays at every frame , problem
		CloseDoorSound = true;
	}
}

float UOpendoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor *> OverlappingActors; // it is an array of object , object of pointer of object AACTOR
	if (!PressurePlate)
	{
		return TotalMass;
	} // for protection of null pointers
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	// Add up their Masses

	for (AActor *Actor : OverlappingActors) // for actor pointer in overlappingactor list
	{

		TotalMass = TotalMass + Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}
void UOpendoor::FindAudioComponent()
{
	AudioComponent = GetOwner()->FindComponentByClass<UAudioComponent>();
	if (!AudioComponent)
	{
		//error
	}
}