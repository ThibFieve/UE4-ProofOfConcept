// Fill out your copyright notice in the Description page of Project Settings.


#include "MyShooterCharacter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "MySimple_ShooterGameModeBase.h"

// Sets default values
AMyShooterCharacter::AMyShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Setting Health
	Health=MaxHealth;


	//////////////////////////// SPAWNING THE GUN////////////////////////////////////

	Gun=GetWorld()->SpawnActor<AGun>(GunClass);
// Level and world is synonim  , we wanna hook up the blueprints calss in teh bluepritns sytem as it is much easier , we 
	///////////////////////////////////////////////////////////////////////////////

	// Hiding the bone/ pre existing gun
	GetMesh()->HideBoneByName(TEXT("weapon_r"),EPhysBodyOp::PBO_None); //EPhysBodyOp::PBO_None is an enum
	Gun->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this); // important for multiplayer and for damage , not for transform hierarchie , useful alter on
	// We doing this so from gun we can do get owner !
}

// Called every frame
void AMyShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this, &AMyShooterCharacter::MoveForward); // Bind axis is a value , bind action is a specific action  , (the text of the binding , to whom it applies, function done)  )
	PlayerInputComponent->BindAxis(TEXT("LookUp"),this, &AMyShooterCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"),this, &AMyShooterCharacter::LookUpRate); // for controller
	PlayerInputComponent->BindAxis(TEXT("MoveRight"),this, &AMyShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"),this, &AMyShooterCharacter::LookRight);
	PlayerInputComponent->BindAxis(TEXT("LookRigthRate"),this, &AMyShooterCharacter::LookRigthRate); // for controller
	PlayerInputComponent->BindAction(TEXT("Jump"),EInputEvent::IE_Pressed,this,&ACharacter::Jump); // To look for parent classs , hit  " ctrl + p " then type character to invesigate.
	// EInputEven is a enum  , press F12 to find 
	PlayerInputComponent->BindAction(TEXT("Shoot"),EInputEvent::IE_Pressed,this,&AMyShooterCharacter::Shoot);
} 

void AMyShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector()*AxisValue) ;// parent function of character , axis value can be positive or negative if we going forward or backwards , Parent class from APawn
}
void AMyShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector()*AxisValue) ;// parent function of character , axis value can be positive or negative if we going forward or backwards , Parent class from APawn
}

void AMyShooterCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue); // parent class  from APawn
}
void AMyShooterCharacter::LookRight(float AxisValue)
{
	AddControllerYawInput(AxisValue); // parent class  from APawn
}

void AMyShooterCharacter::LookUpRate(float AxisValue) // axis value is between 0 and 1
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds()); // parent class  from APawn  , Value . RotationRate gives a speed , multiply this by delta time we get a distance.
	// This is only necessary for controller inputs ! not for mouse inputs
}

void AMyShooterCharacter::LookRigthRate(float AxisValue) // axis value is between 0 and 1
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds()); // parent class  from APawn  , Value * RotationRate gives a speed , multiply this by delta time we get a distance.
	// This is only necessary for controller inputs ! not for mouse inputs
}

void AMyShooterCharacter::Shoot()
{
	Gun->PullTrigger();
}


// OVERIDING THE PARENT METHOD !
float AMyShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) 
{
	float DamageToApply = Super::TakeDamage( DamageAmount, DamageEvent, EventInstigator,  DamageCauser); // we call the parent implementation ,
	// good practice as we dont know waht is being processes in the base method
	DamageToApply= FMath::Min(Health,DamageToApply); // so it doesnt go in negative numbers
	Health= Health - DamageToApply ;
	UE_LOG(LogTemp,Warning,TEXT("Health Left %f"), Health);

	if(IsDead())
	{
		
		//TO end the game

		AMySimple_ShooterGameModeBase* GameMode= GetWorld()->GetAuthGameMode<AMySimple_ShooterGameModeBase>();
		if(GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}


		//detach the controller
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	}

	return DamageToApply;
}


bool AMyShooterCharacter::IsDead() const
{
	if (Health <= 0.f)
	{
		return true;
	}
	return false;
}


float AMyShooterCharacter::GetHealthPercent() const
{
	return Health/MaxHealth;

}