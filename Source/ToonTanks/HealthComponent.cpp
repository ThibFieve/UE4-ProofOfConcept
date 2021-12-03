// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health=MaxHealth;
	// ...


	// The delegate  , is on the actor that owns this component of health , and we want to bind DamageTaken to that delegate on the Actor , lesson 158 
	GetOwner()->OnTakeAnyDamage.AddDynamic(this,&UHealthComponent::DamageTaken); // damage taken is bound to OnTakeAnyDamage and is bound to the invocation list of it
	// Any damage event will generate a broadcast from OnTakeAnyDamage that will call all teh function in the Invocation list


	//let's get the gamemode !
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this)); // we need to cast again because it returns the BaseGamemode and not a toon tank game mode

	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ... 
}
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage,const UDamageType* DamageType, class AController* Instigator, AActor*  DamageCauser)
{
	// The delegate  , is on the actor that owns this component of health , and we want to bind DamageTaken to that delegate on the Actor
	if(Damage<= 0.f) return;
	
	Health= Health - Damage ; // Health -= Damage

	if (Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor); // call the toon tank game mode and call actor died 
	}
	
}





//Every object (in the general sense of an "object" in a C++ program, not only UObjects) are represented as "classes" in code (and everything is code in Unreal, even Blueprints under the hood).

//A class represents a cohesive unit of code, an abstract entity in you game/application, so Actors and Components are both implemented as classes.

//Actors are the class that represents a game entity, with its own identity (a tank, an enemy tower), while components are added to the Actor to provide the logic, what makes the game what it is.

//Classes are not the objects themselves, but "recipes" for building instances, the runtime objects that live in your game/application.

//The relation between a Pawn class and an Actor class is that a Pawn IS-A Actor.

//The relation between an Actor class and a Component class is that an Actor HAS-A component (look up inheritance and composition, as well as other OOP concepts).

//They're both classes (they couldn't be anything else) !
