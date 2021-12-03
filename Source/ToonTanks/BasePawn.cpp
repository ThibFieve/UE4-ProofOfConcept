// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "ProjectileClass.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// RootComponent; type USceneComponent , check the slides , it's the default component , if we want collision or a capsule component, 
	//we need to make it repalce that defautl component , then we can attach other component to that componant , attach to the collision
	//Uscenecomponent is a general class that has a transform , posistion , but no visual represenation (good for missile spawn), Capsulecomponent is a child class that has capsul (collision capsule)
	//, Meshcomponent is a child with a visual
	// you can attach component to those componenet




	//Template function

	//See slides
	//CreateDefaultSubobject <>() is a tempalte function , the type is given in the brackets ,  and the argument between the parenthesis is a name (use TEXT macro) , returns an adress of UStaticMeshComponent just created

	// include Ucapsulecomponent
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp; // this makes it the root compoennt of the pawn is the collision volume 
    // check the video , we can actually do that super easily through the blueprints , but he choses how to do it through both cpp and blueprints

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp); // we attach the basemesh to the capsule

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh); // attach turret to base mesh 

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
	
}

void  ABasePawn::HandleDestruction()
{
	// VISUAL AND SOUND EFFECT WHEN DYING
	if(DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles , GetActorLocation(),GetActorRotation());

	}
	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,DeathSound,GetActorLocation());
	}
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}

	

}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget= LookAtTarget - TurretMesh->GetComponentLocation(); // Totarrget is a world space director vector , so we dont use local offset !
	FRotator LookAtRotation =FRotator(0.f, ToTarget.Rotation().Yaw,0.f);
	//LookAtRotation.Pitch=0.f;
	//LookAtRotation.Roll=0.f;
	TurretMesh->SetWorldRotation(LookAtRotation) ;

}

void ABasePawn::Fire()
{
	// Access Mapping is called every frqme and call the function and feed it the vqlue of the key input ,  use bindaxis
//whereas action mapping is only calling the function  when the chosen key is pressed.  use bindaction


	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();

	/////////////////////////////////////////////////////////////////////////////////////////////////DEBUG SPHERE ////////////////////////////////////////
    
	//DrawDebugSphere(
	//	GetWorld(),
	//	ProjectileSpawnPointLocation,
	//	25.f,
	//	12,
	//	FColor::Red,
	//	false,
	//	3.f);
	/////////////////////////////////////////////////////////////////////////////////////////////////DEBUG SPHERE ////////////////////////////////////////




	auto Projectile = GetWorld()->SpawnActor<AProjectileClass>(ProjectileClass,ProjectileSpawnPointLocation,ProjectileSpawnPoint->GetComponentRotation()); // it tqkes the Uclass object , the location , the rotation
	// SpawnActor retunrs a pointer to the spawned actor
	// auto  , allows the compiler to figure out the type of a variable
	Projectile->SetOwner(this); // this means that if we spawn a projectile , its owner will be set as being BasePawn , the instance of the class that owns that projectile!
 


}




// Called every frame
//void ABasePawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);



	// EXPERIMENTAL CODE //////////////////////////////////////////

	//FVector DeltaLocation(0.f); // see definition of FVectorS
	//DeltaLocation.X = 2.f;

	//AddActorLocalOffset(DeltaLocation); // first parameter is optional 

	// EXPERIMENTAL CODE //////////////////////////////////////////

//}


