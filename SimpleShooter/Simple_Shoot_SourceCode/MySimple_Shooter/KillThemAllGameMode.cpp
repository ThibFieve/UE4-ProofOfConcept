// Fill out your copyright notice in the Description page of Project Settings.


#include "KillThemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAiController.h"

void AKillThemAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    if (PlayerController != nullptr)
    {
        //PlayerController->GameHasEnded(nullptr,false); //game has ended is a function on all controller , either Ai or player , lets notify the AI
        EndGame(false);
    }
    for(AShooterAiController* AIController : TActorRange<AShooterAiController>(GetWorld()))
    {
        if(AIController->IsDead() == false)
        {
            return; // game is not over
        }
        
    }
    
        EndGame(true); // game is over , player has won , all 'player controller should be notified
    


}

void AKillThemAllGameMode::EndGame(bool bIsPlayerWinner)
{
    // How can we found all controller and do game has ended
    for(AController* Controller : TActorRange<AController>(GetWorld()))// get us a list of all the controllers , get all the controller in the world , in the level
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner ;
        Controller->GameHasEnded(Controller->GetPawn(),bIsWinner);
        
        
    } 

}