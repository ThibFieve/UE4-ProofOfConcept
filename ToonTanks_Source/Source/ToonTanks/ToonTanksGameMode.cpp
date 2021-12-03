// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include"ToonTanksPlayerController.h"



void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if(DeadActor == Tank)
    {   
        Tank->HandleDestruction(); // we call the handle destruction from the tank class
        if(Tank->GetTankPlayerController()) // we made that function to get the controller easily
        {


            ToonTanksPlayerController->SetPlayerEnabledState(false);


            // IF WE DIDNT MAKE THAT  HAND MADE TOONTANKCONTROLLER player controller calsse we would do this : /////////////////////////////////////////////////////////////////////////////
           
            //Tank->DisableInput(Tank->GetTankPlayerController());// we call disable input , built in function , take in a player controller
            //Tank->GetTankPlayerController()->bShowMouseCursor=false; // make sure the mouse cursos is not shown


            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }
        GameOver(false);
         
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)) // let's see if we can cast the dead actor to a tower , we make a local variable Destroyed Tower
    {
        DestroyedTower-> HandleDestruction();
        TargetTowers--;
        if(TargetTowers == 0)
        {
            GameOver(true);
        }
    }

}


 void AToonTanksGameMode::BeginPlay() 
 {
     Super::BeginPlay();
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0)); // we need to cast , Ugameplay statioc, sstatic calsses that are really useful  ! Static means it is a glbal function and can be called by anyone
    ToonTanksPlayerController = Cast<AToonTanksPlayerController> (UGameplayStatics::GetPlayerController(this,0)); // THIS IS ANOTHER WAY TO GET the controller !

    HandleGameStart();



 }

 void AToonTanksGameMode::HandleGameStart()
 {
     // start countdown to disable, enable input

     TargetTowers = GetTargetTowerCount();

    if(ToonTanksPlayerController) 
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false); // if we dont ahve a controller then no mouse  and inout
        FTimerHandle PlayerEnabledTimerHandle;


        StartGame(); //Blueprint implemetable events , lesson 164 , function called in C++ but implemented in bluepritns they cannot be private.s


        // We will know create our own timer delegate , a strucutre that holds  a list of invocation of function and calls all of thme when it is changed

        FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController , &AToonTanksPlayerController::SetPlayerEnabledState,true ); // the tre inputs are
        // the user object the class of the callback function exists on  ,adress of the  the Callback function , the input of that callback function that will be passed 
        //remark when passing a adress of a fucntion dont put thte ()

        GetWorldTimerManager().SetTimer(  // it is an overload 
        PlayerEnabledTimerHandle, // Timer handle
        TimerDelegate, // Timer delegate
        StartDelay, // Delay before using
        false // we dont want to loop 
        );
    };
    
    
    

    
 }

    int32 AToonTanksGameMode::GetTargetTowerCount()
    {
         TArray<AActor*> Towers;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(),ATower::StaticClass() ,Towers) ; //ATower::StatiClass() returns teh Uclass !
        return Towers.Num();
    }