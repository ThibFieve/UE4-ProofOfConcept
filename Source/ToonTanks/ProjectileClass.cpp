// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileClass.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectileClass::AProjectileClass()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;


 	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile  Movement Component"));
	MovementComponent->MaxSpeed=1300.f;
	MovementComponent->InitialSpeed=1300.f;

	TrailParticles= CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectileClass::BeginPlay()
{
	Super::BeginPlay();

	//////////// BINDING THE MULTICAST DELEGATE ///////////
	BaseMesh->OnComponentHit.AddDynamic(this,&AProjectileClass::OnHit); // This bound the function OnHit to OncomponentHit, on component hit is a varaible of Ubasemesh, It is a variable 
	//but also a structure and a Multicast delegate . it mean that everytime there is somethign changing it calls it invocation list , a list of function ! this is called broadcast see lesson 157
	//////////// BINDING THE MULTICAST DELEGATE ///////////


	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,LaunchSound,GetActorLocation());

	}
}

// Called every frame
void AProjectileClass::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//OnHit function must have a particular signature to be able to be the callback in the multicast delegate 
void AProjectileClass::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,UPrimitiveComponent* OtherComp,FVector NormalImpulse, const FHitResult& Hit)
{
	// HitComp is the component we are talking about , Otheractor is the other actor being hit , OtherComp is the other component , normal impulse is how to object is bouncing , hitresult strcut with many info
	
	// Debugging !
	UE_LOG(LogTemp,Warning,TEXT("OnHit"));

	UE_LOG(LogTemp,Warning,TEXT("HitComp: %s"),*HitComp->GetName()); // componetn doing the hitting
	UE_LOG(LogTemp,Warning,TEXT("OtherActor: %s"),*OtherActor->GetName()); // Actor being hit 
	UE_LOG(LogTemp,Warning,TEXT("OtherComp: %s"),*OtherComp->GetName()); //  Component being hit

////// PARTICLE SYSTEM//////////
UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());





	// APPLYING DAMAGE

	auto MyOwner = GetOwner(); //auto  , allows the compiler to figure out the type of a variable
	if(MyOwner == nullptr)
	{
		Destroy();
		return;
	}  // check for null pointer

	auto MyOwnerInstigator = MyOwner->GetInstigatorController(); // a pointer to the instigator of the damage 

	auto DamageTypeClass = UDamageType::StaticClass(); // we want a UClass of the class UDamageType , to do so we can call a static function called StaticClass , we could use TSubClassOf ...

	if(OtherActor && OtherActor !=this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor,Damage,MyOwnerInstigator,this,DamageTypeClass);

		 // SUPER EASY , DESPAWN THE PROJECTILE 

		if(HitParticles)
		{////// PARTICLE SYSTEM//////////
		UGameplayStatics::SpawnEmitterAtLocation(this,HitParticles,GetActorLocation(),GetActorRotation());
			
		}
		if(HitSound) // SOUND EFFECT
		{
			UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation()); // first paramter is world object
		}
		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		


	}
	Destroy();

}

