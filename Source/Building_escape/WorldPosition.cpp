// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true; // if set to fqlse , this instqnce of teh component would not be updated every frame
	
	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();
  //super begin play means everything up the high hierarchy has to be ran first
	// ... when the world is initialised this will begin






	int32 Number =9 ;
	// int is q primitives , there is no such thing qs Number.smth()
	FString Log= TEXT("hello");

	FString *PrtLog = &Log;  // FString is the objcet the pointer referes to, so here the pointer PrtLog is the qdress of Log
	Log.Len();
	//*PrtLog. // this wouldnt work becaus the dot operator has higher presidence over dereferencing , it will do the dot first
	(*PrtLog).Len();// this gives us the same as previous Log.Len()
	PrtLog->Len();// does the same, goes via a poitner  
	// there is q Cpp operqtor precedence list with what takes palce firsts

	FString ObjectName = GetOwner()-> GetName(); // this GetOwner() gives a pointer of an actor
	UE_LOG(LogTemp,Warning,TEXT("The object name is %s"),*ObjectName);

	// ways to amke a log
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Log); // * means overloading in this cqse , not poiutner , this must be used when its a string,  stqr is used for mult , poitner deference, qnd overloqding
	// If ze types *PrtLog it would not compile it would fail, tho **PrtLog will work !dereference adn then overload operator

	// Error makes it red , Warning is yellow, Display is grey
	// go in windows setting and put output log every obejct of this class  will emit the log





	FString ObjectPosition = GetOwner()-> GetActorLocation().ToString(); // check Fvector on UE documentation , actor location gives a Fvesctor and we .tostring to get a fstring

	UE_LOG(LogTemp,Warning,TEXT("The object %s position is %s "),*ObjectName,*ObjectPosition);




}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
		// this will be ran every frame of the game
	// ...
}



// UE manipulation , with a material , you can create a material isntance wwhich will inherit everyting from the base material , but if you modify it it wont affect
//all the other object using the same material.
//better import Png over the otehrs

