// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);  

    // Find the distance to the Tank,
    if(InFireRange())
    {
        
            Super::RotateTurret(Tank->GetActorLocation()); 
        
        
    }

    

    
}
void ATower::HandleDestruction()
{
   Super::HandleDestruction(); // call theparetn class
   Destroy();
}

 void ATower::BeginPlay()
 {
     Super::BeginPlay();
     Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));  // will get us APawn but Tank is ATank , a child class we need to cast, cannot store a parent in a child varaible


    GetWorldTimerManager().SetTimer(FireRateTimeHandle , this , &ATower::CheckFireCondition,FireRate,true);//does the function Checkfire every firerate .it uses a  FTimerHandle handle 

 }
 void ATower::CheckFireCondition()
 {
    if(Tank == nullptr)
    {
       return;
    }
       if(InFireRange() && Tank->bAlive)
    {
        
      Super::Fire(); // can also call ATank::Fire() or just Fire()
        
    }

 }

 bool ATower::InFireRange()
 {
       if(Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        if (Distance <= FireRange)
        {
           return true; // can also call ATank::Fire() or just Fire()
        }
        
        
    }

    return false;

 }