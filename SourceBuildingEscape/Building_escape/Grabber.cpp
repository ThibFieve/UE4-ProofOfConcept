// Copyright thibault Fievez 2020

#include "GameFramework/Controller.h"
#include "Engine/World.h"

#include "Math/Vector.h"

#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h" // to be able to draw a line debug help

#include "Grabber.h" // must be at the end

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
	UE_LOG(LogTemp, Warning, TEXT("Grabber is there"));

	FindPhysicHandle();

	SetupInputComponent();

	
}

void UGrabber::SetupInputComponent()
{
	// KEY MAPPING !  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Input componenet is a bit hidden away , all Aactor have input component !
	//again we want to protect ourselves , lesson 44
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>(); // lesson 44

	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputcomponentfound"));
		// IE= input event, &grabber , it is teh adress to the function Grab from the class UGrabber , :: is scope operator
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab); // Grab is the name we gave in the project setting in input !  this happens when Input even pressed ! when we presss the key down
		// this is a pointer to the object , the isntance of the class that is executed in this code , not a reference to the class itslef !
		//last element of Bindaction takes an adress of a function Grab , this is so , whenver this key is press it will call this particluar function grab
		// mapped user input to a function
		/////////////////////////////////////////////////SEE LESSON 45/////////////////////////////////////////////////////////
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Inputcomponent not found"));
	}
}

void UGrabber::FindPhysicHandle()
{
	//Checkung for physic handle component
	//the only way is to get the owner and see what compoentns it has
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>(); // specify the class we looking for in <> , gives out the first of that types it finds
	//FindComponentByclass is a function tempalte , we need to use <>, we will tell what class we are looking for in particular. Returns the first physics handle component found
	// lesson 43//

	if (PhysicsHandle) // to protect us from crashed !
	{
		//physics is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The linetrace object hit is %s , it needs to have a PhysicHandle component to be able to be grabbed or grab"), *(GetOwner()->GetName()));
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Graber Release"));

	//TODO remove release physic handle !
	if(!PhysicsHandle){return;}
	PhysicsHandle->ReleaseComponent();

}

void UGrabber::Grab()
{



	

	UE_LOG(LogTemp, Warning, TEXT("Graber Pressed"));
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	// TODO If we hit something then attach hysics handle

	UPrimitiveComponent* ComponentToGrab= HitResult.GetComponent();

	if(HitResult.GetActor())// HitResult.GetActor() isa  a poitner
	{ if(!PhysicsHandle){return;}
	PhysicsHandle->GrabComponentAtLocation
	(

		ComponentToGrab,
		NAME_None,
		GetPlayerReach()

	);
	}
	
}




// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...


	// IF there is object we can move it !
	if(!PhysicsHandle){return;}
	if(PhysicsHandle->GrabbedComponent){

		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}

	
}

// KEY MAPPING !
// Input componenet is a bit hidden away , all Aactor have input component !

// LESSON  how ARROW -> n dot . , and :: accessors worrk LESSON 45!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Virtual memory
//Permanent Storare , stack and heap




FHitResult UGrabber::GetFirstPhysicsBodyInReach() const // UNrefactored !//
{

// get player viewpoint
	FVector PlayerViewPointLocation; // those are gonna be modified
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // watchout Getplayerview has out parameter , which means pass by reference and will cahnge the object of the pointer passed as input
	//UE_LOG(LogTemp,Warning,TEXT("The location is %s , the rotation is %s"), *PlayerViewPointLocation.ToString(),*PlayerViewPointRotation.ToString());
	// we want to dereference  the fstring
	//Logging out to test



/////////////////////////////////////////////////////////////////////////////Debugging Raycast ////////////////////////////////////////////////////////////////
	// Ray-casting to a certain distance
	//Draw a line from player showing the reach 
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach; // line from center of world all the way to the end of the reach of the player , here reach
																							   // PlayerViewPointRotation.Vector() gives a unit vector , see lesson 38
	DrawDebugLine(																			   // should be green line of 5 pixel of width from palyer up to  reach
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(0, 255, 0), //green
		false,
		0.f,
		0,
		5.f // 5 pixels
	);

	/////////////////////////////////////////////////////////////////////////////STOP Debugging Raycast ////////////////////////////////////////////////////////////////

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner()); // constructor ! first parameter is the one that detaisl if the object is valid to be grabbed ,complex collision ? false
	// third input is what actor we need to ignore of course we need to remover owner as we constantly hit it first
	// see documentation , we need to ignore oruself because the raycasting got trhough our boyd object
	//get owner, owmer will be ignored as we are having the grabber as a component !

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit, // out parameter !
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), //collision channelk is physic type ! Ecollisionchannel is a enum , to access any memeber of it we gotta use a ::
		TraceParams);													 // out param here as well

	// LOGOUT THE ACOTR HIT ; WE WILL DO A IF TO GET RID OF NULL POINTERS

	AActor *ActorHit = Hit.GetActor();

	if (ActorHit) // if not null
	{
		UE_LOG(LogTemp, Warning, TEXT("The linetrace object hit is %s "), *(ActorHit->GetName())); //fstring have to be derefernecend when passed as log
	}
	//see what we hit

	// next step give a physic handle to us the carachter but also to the object we can grab!

	return Hit;
}

FVector UGrabber::GetPlayersWorldPos() const{

	FVector PlayerViewPointLocation; // those are gonna be modified
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); 
	
	return PlayerViewPointLocation ;

}


FVector UGrabber::GetPlayerReach() const
{
	
	// get player viewpoint
	FVector PlayerViewPointLocation; // those are gonna be modified
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation); // watchout Getplayerview has out parameter , which means pass by reference and will cahnge the object of the pointer passed as input
	
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;


}