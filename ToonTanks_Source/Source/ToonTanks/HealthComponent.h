// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) ) // THIS MAKES IT SO WE CAN ASSIGN IT IN BLUEPRINTS , created by default for an actor componetn class
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	float MaxHealth =100.f;
	float Health = 0.f;
  // MULTICAST DELEGATE CALLBACK FUNCTION , here for the damage
	UFUNCTION()
	void DamageTaken(AActor* DamagedActor, float Damage,const UDamageType* DamageType, class AController* Instigator, AActor*  DamageCauser); // forwarded decalred instigator is the controller responsible for the dmage can be null
   // Damage causer is the actual actor that cause the damage , not the controller 
   // MULTICAST DELEGATE CALLBACK FUNCTION , here for the damage


   class AToonTanksGameMode* ToonTanksGameMode; // forward delcare , we wanna be able to call public function of the ToonTanksGameMode
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
