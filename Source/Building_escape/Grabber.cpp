// Copyright thibault Fievez 2020

#include "GameFramework/Controller.h"
#include "Engine/World.h"

#include "Math/Vector.h"


#include "DrawDebugHelpers.h" // to be able to draw a line debug help

#include "Grabber.h"// must be at the end



#define OUT // we create that m, it's a macro like TEXT , to show that its a out paramter , it passses by  reference and changes the content of the object
//it does nothing CODE WHISE , it's jsut for readability !


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	UE_LOG(LogTemp,Warning,TEXT("Grabber is there"));

	//Checkung for physic handle component 
	//the only way is to get the owner and see what compoentns it has 
	PhysicsHandle = GetOwner()-> FindComponentByClass<UPhysicsHandleComponent>();
	//FindComponentByclass is a function tempalte , we need to use <>, we will tell what class we are looking for in particular. Returns the first physics handle component found
	// lesson 43
	if(PhysicsHandle)
	{
		//physics is found
	}
	else
	{
		UE_LOG(LogTemp,Error,TEXT("The linetrace object hit is %s , it needs to have a PhysicHandle component to be able to be grabbed or grab"), *(GetOwner()->GetName()) );
	}
// KEY MAPPING !  
// Input componenet is a bit hidden away , all Aactor have input component !
//again we want to protect ourselves , lesson 44
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

if(InputComponent)
{
	UE_LOG(LogTemps,Warning,TEXT("Inputcomponentfound"));

	InputComponent->BindAction("Grab",IE_Pressed, this, &UGrabber::Grab );// Grab is the name we gave in the project setting in input !  this happens when Input even pressed ! when we presss the key down
	// this is a pointer to the object , the isntance of the class that is executed in this code , not a reference to the class itslef !
	//last element of Bindaction takes an adress of a function Grab , this is so , whenver this key is press it will call this particluar function grab
	// mapped user input to a function
}else
{
	UE_LOG(LogTemps,Warning,TEXT("Inputcomponent not found"));
}

}


void UGrabber::Grab()
{
	UE_LOG(LogTemps,Warning,TEXT("Graber Pressed"));

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	// get player viewpoint
   FVector PlayerViewPointLocation;// those are gonna be modified
   FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // watchout Getplayerview has out parameter , which means pass by reference and will cahnge the object of the pointer passed as input
	UE_LOG(LogTemp,Warning,TEXT("The location is %s , the rotation is %s"), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString()); // we want to dereference  the fstring
	//Logging out to test

	// Ray-casting to a certain distance 
	//Draw a line from player showing the reach
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach ; // line from center of world all the way to the end of the reach of the player , here reach
    // PlayerViewPointRotation.Vector() gives a unit vector , see lesson 38
	DrawDebugLine( // should be green line of 5 pixel of width from palyer up to  reach 
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255 ,0), //green
		false,
		0.f,
		0,
		5.f // 5 pixels
	);
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")),false, GetOwner()); // constructor !
	

	 // see documentation , we need to ignore oruself because the raycasting got trhough our boyd object
	//get owner, owmer will be ignored as we are having the grabber as a component !
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,
	PlayerViewPointLocation,
	LineTraceEnd,
	FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //collision channelk is physic type ! Ecollisionchannel is a enum , to access any memeber of it we gotta use a ::
	TraceParams
	) ;// out param here as well
	

	// LOGOUT THE ACOTR HIT ; WE WILL DO A IF TO GET RID OF NULL POINTERS

	AActor* ActorHit= Hit.GetActor();

	if(ActorHit) // if not null
	{
		UE_LOG(LogTemp,Warning,TEXT("The linetrace object hit is %s "), *(ActorHit->GetName())); //fstring have to be derefernecend when passed as log

	}
	//see what we hit 


	// next step give a physic handle to us the carachter but also to the object we can grab!
}




// KEY MAPPING ! 
// Input componenet is a bit hidden away , all Aactor have input component !