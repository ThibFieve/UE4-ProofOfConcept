// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h" // we need that calss to create widget "!" , this is in another module than the standard one so we add to ahd in my simpleshooter.build the module "UMG" 




void AShooterPlayerController::BeginPlay() 
{
    Super::BeginPlay();
     HUD=CreateWidget(this,HUDClass);
        if(HUD != nullptr)
        {
           HUD->AddToViewport();
        }
}


void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus,bIsWinner);
    HUD->RemoveFromViewport();
    if(bIsWinner)
    {      
        UUserWidget* WinScreen=CreateWidget(this,WinScreenClass);
        if(WinScreen != nullptr)
        {
           WinScreen->AddToViewport();
         }
        GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);

    }
    else{
        UUserWidget* LoseScreen=CreateWidget(this,LoseScreenClass);
        if(LoseScreen != nullptr)
        {
           LoseScreen->AddToViewport();
         }
        GetWorldTimerManager().SetTimer(RestartTimer,this,&APlayerController::RestartLevel,RestartDelay);


    }
    

}