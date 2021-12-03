// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "MyShooterCharacter.h"
// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void  AGun::PullTrigger()
{
	UE_LOG(LogTemp, Warning, TEXT("You have been shot !"));
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash,Mesh,TEXT("MuzzleFlashSocket")); // Fname is the socket name ! Socket that is attached to the bone 
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh,TEXT("MuzzleFlashSocket"));

	FHitResult HitObject;
	FVector ShotDirection;
	bool bHit =GunTrace(HitObject,ShotDirection);

	
	if (bHit)
	{
		
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),Impact ,HitObject.Location, ShotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(),HitSound,HitObject.Location,ShotDirection.Rotation());

		 // DrawDebugPoint(GetWorld(),HitObject.Location,40,FColor::Red,true); ////////////////////////////////////////////// DEBUG HIT ////////////////////////////

		// Applying Damage !

		

		AActor* HitActor = HitObject.GetActor(); // need to check if not null
		if(HitActor != nullptr) // Unreal doesnt like to call function of pointers that are null
		{
			FPointDamageEvent DamageEvent(Damage,HitObject,ShotDirection,nullptr); // See definitom of Hitactor and see waht we need , then see definition of FPointDamage

			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage,DamageEvent,OwnerController,this);
		}


	}
	



}

bool AGun::GunTrace(FHitResult& outHit, FVector& outShotDirection)
{
		// DEBUG CAMERA !//
	//DrawDebugCamera(GetWorld(),GetActorLocation(),GetActorRotation(), -90 , 2 , FColor::Red, true);



	AController* OwnerController = GetOwnerController();
	if(OwnerController == nullptr)
	{
		return false;
	}
		

	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location,Rotation); // This is using out paramters ! See definitions !  There is no syntax helpfullness to realise that , just gotta be caraeful !
	 outShotDirection = -Rotation.Vector(); // where the shot is coming from 
		// HERE FOR AI WE GET AN ISSUE AS ITS VIEWPORT IS INSIDE THE ACTOR CAPSULE


	  // DrawDebugCamera(GetWorld(),Location,Rotation, 90 , 2 , FColor::Red, true);  ////////////////////////////////////////////// DEBUG Camera Position //////////////////////////// 
 

	FVector End= MaxRange * Rotation.Vector() + Location ;

	 //out paramter of the function coming
	FCollisionQueryParams Params; // To avoid shooting yourself !
	Params.AddIgnoredActor(this); //ignore the gun
	Params.AddIgnoredActor(GetOwner()); // ignore the owner of the gun, the MyShooterCaracter that owns it
	return GetWorld()->LineTraceSingleByChannel(outHit,Location,End, ECollisionChannel::ECC_GameTraceChannel1,Params ); // HitObject is a out parameter , see the definition
	// ECollisionChannel is an enum 

	
}


 AController* AGun::GetOwnerController() const
{

	// WE can use get owner simply because in myshooter.ccp we used Gun->SetOwner(this); The link is not for postition transform but simply for code and logic
	APawn * OwnerPawn =Cast<AMyShooterCharacter>(GetOwner());
	if(OwnerPawn == nullptr)return nullptr;
	
	return OwnerPawn->GetController();
	
}
