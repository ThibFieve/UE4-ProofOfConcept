// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyShooterCharacter.generated.h"


class AGun; //Forward declare 


UCLASS()
class MYSIMPLE_SHOOTER_API AMyShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	// WE OVERRIDE THAT METRHOD FROM ACTOR
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;



// WE WANT A GET METHOD TO BE ABLE TO EXTRACT THE BOOLEAN ISDEAD OR NOT FROM BLUEPRITNS ! UFUNCTION ! /////////////////////////////

	UFUNCTION(BlueprintPure) // BlueprintPure is doing  BlueprintCallable and more
	bool IsDead() const;// we dont expect is to change the stae of the shooter character
	//BluePrintPure means that there is not an execution pin ! should be cosnt and not chagne teh stae of waht has been called !
	UFUNCTION(BlueprintPure) 
	float GetHealthPercent() const;
	
	void Shoot();
	private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue);
	void MoveRight(float AxisValue);
	void LookRight(float AxisValue);
	


	// FOR the gamepad we need to create framerate independancy see lesson 179
	UPROPERTY(EditAnywhere)
	float RotationRate =50;
	void LookUpRate(float AxisValue);
	void LookRigthRate(float AxisValue);

	UPROPERTY(EditDefaultsOnly) // so we cannot cahnge at run time , begin play would ahve already been called so nothing would be updated
	TSubclassOf<AGun> GunClass; // that is for forcing the blueprints only to allow subclass of AGun !
	UPROPERTY()
	class AGun* Gun; // that is where we store the instance of the class 
// fprward declare , we can also write class AGun, at the top



	UPROPERTY(EditDefaultsOnly) // becasue only used in begin play so if you change while on runtime it wont have impact
	float MaxHealth =100;
	UPROPERTY(VisibleAnywhere) // becasue only used in begin play so if you change while on runtime it wont have impact
	float Health ;
};
