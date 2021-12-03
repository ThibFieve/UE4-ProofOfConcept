// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "MyShooterCharacter.h"

void AShooterAiController::BeginPlay()
{
    Super::BeginPlay() ;// always do that , good practice , there are probably things we missing out if not doing it  

   if(AIBehavior != nullptr)
   {

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);  // We want to get hold of the Pawn actor , we can use something from the GamePlayStatics !

       RunBehaviorTree(AIBehavior);
      // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());

     GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"),GetPawn()->GetActorLocation());
   }

   
}

void AShooterAiController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); // always do that , good practice , there are probably things we missing out if not doing it , as a matter of fact if you dont do it , the Ai controller wont look at you
    
    
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);  // We want to get hold of the Pawn actor , we can use something from the GamePlayStatics !
    


    ////////////////////////////////////////////// BAREBONE AI , LETS USE A BEHAVIROU TREE INSTEAD ! /////////////////////////////////////////////////////////////////

    // iF LINE OF SIGHT
        // MoveTo
        //SetFocus
    //Else
        //ClearFocus
        //StopMovement

   // if (Super::LineOfSightTo(PlayerPawn))  // THE SUPER is not necessary , as this child class has the methods of th paretns AIController but just for un or clarirty its there
   // {
    //    Super::SetFocus(PlayerPawn); // Super is unnecessary as but let's see
    //    Super::MoveToActor(PlayerPawn, AcceptanceRadius);
   // }
    //else{
    //    Super::ClearFocus(EAIFocusPriority::Gameplay);
    //    Super::StopMovement();

  //  }



  //NEW METHOD FOR AI

     if(AIBehavior != nullptr)
   {

       //RunBehaviorTree(AIBehavior);
       if (Super::LineOfSightTo(PlayerPawn))  // THE SUPER is not necessary , as this child class has the methods of th paretns AIController but just for un or clarirty its there
    {

        //Becasue we made it in services in teh behaviour tree we dont need those no more
       // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"),PlayerPawn->GetActorLocation());
       // GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"),PlayerPawn->GetActorLocation());
    }
    else{
        //Becasue we made it in services in teh behaviour tree we dont need those no more
       // GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    }

       
   }

    




    
    // AI Movement
    /*
    * NAV MESH for gicing the naviagualbe surface to AI , calculate what is a route the AI can take and what is too steep for them , it allows the Ai to do its routing algorithhm on it
    */


    ////////////////////////////////////////////// BAREBONE AI , LETS USE A BEHAVIROU TREE INSTEAD ! /////////////////////////////////////////////////////////////////

}

bool AShooterAiController::IsDead() const
{
   AMyShooterCharacter* ControllerCharacter = Cast<AMyShooterCharacter>(GetPawn());
   if(ControllerCharacter)
   {
       return ControllerCharacter->IsDead(); // wll see if the carachter attached to this controller is alive or not
   }
   else
   {
       return true ; // if not controlling a pawn then it is dead !
   }
}
