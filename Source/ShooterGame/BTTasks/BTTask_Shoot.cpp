// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "ShooterGame/Characters/PlayerCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}



EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APlayerCharacter* AICharacter = Cast<APlayerCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	if (!AICharacter)
		return EBTNodeResult::Failed;

	AICharacter->Fire();

	return EBTNodeResult::Succeeded;
}