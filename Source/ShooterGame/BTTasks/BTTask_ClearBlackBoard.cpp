// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_ClearBlackBoard.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ClearBlackBoard::UBTTask_ClearBlackBoard()
{
	NodeName = TEXT("Clear Blackboard");
}


EBTNodeResult::Type UBTTask_ClearBlackBoard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
	return EBTNodeResult::Succeeded;
}
