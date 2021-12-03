// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "MyShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
    NodeName = TEXT("Shoot");
}
EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask( OwnerComp,  NodeMemory);
    
    //OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());

    // We wanna yse the Shoot() of MyShooterCarachter
    if(OwnerComp.GetAIOwner() ==nullptr)
    {
        return EBTNodeResult::Failed ;
    }

    AMyShooterCharacter* Character = Cast<AMyShooterCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    if(Character == nullptr)
    {
        return EBTNodeResult::Failed ;
    }
    Character->Shoot();

    return EBTNodeResult::Succeeded ;

}