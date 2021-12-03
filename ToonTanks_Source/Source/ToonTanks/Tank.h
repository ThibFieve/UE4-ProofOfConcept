// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:
	ATank(); // constructor

	public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool bAlive = true;



	APlayerController* GetTankPlayerController() const {return TankPlayerController;} // const , not designed to cahnge anything in this class,
	//we can define it within the .h file

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override; // player input is forward declared here


	void HandleDestruction();
     protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





	private:
	

	UPROPERTY(EditAnywhere, Category = "Movement") //BluePrintReadWrite its to be accessible in the event graph , editanywehre means can edit for isntance and class
	float SpeedTank = 200.f;
	UPROPERTY(EditAnywhere, Category = "Movement") //BluePrintReadWrite its to be accessible in the event graph , editanywehre means can edit for isntance and class
	float RotationTank = 200.f;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm; // need to forward declare with class (as we did not include the .h of spring compoentn in this .h file , but will only include it in the tank.cpp file )
	// this is made to avoid carry over all bunch of .h when doing child classes and what not , and just use the spring arm compoennt if need be in the .cpp file
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;


	// private function
	void Move(float Value);

	void Turn(float Value);


	APlayerController* TankPlayerController;
	
};

