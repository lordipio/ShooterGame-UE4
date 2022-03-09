// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGame/Characters/PlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AShooterCharacterAIController::BeginPlay()
{
	Super::BeginPlay();

	PlayerActor = Cast<AActor>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (BehaviorTree && (GetWorld()->GetMapName() == "UEDPIE_0_Map1") && PlayerActor)
	{
		RunBehaviorTree(BehaviorTree);
		GetBlackboardComponent()->SetValueAsObject("PlayerPawn", UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	}

}


void AShooterCharacterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	EnemyDepthOfField = FVector::Dist(PlayerActor->GetActorLocation(), GetCharacter()->GetActorLocation());

	if (LineOfSightTo(PlayerActor) && EnemyDepthOfField < 2000.f)
	{
		GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 700.f;
		GetBlackboardComponent()->SetValueAsVector("PlayerLastLocation", PlayerActor->GetActorLocation());
		bAICanSeePlayer = true;
	}

	if (!LineOfSightTo(PlayerActor))
	{
		if (GetCharacter())
		{
			GetCharacter()->GetCharacterMovement()->MaxWalkSpeed = 250.f;
		}
		bAICanSeePlayer = false;
	}

	GetBlackboardComponent()->SetValueAsBool("AICanSeePlayer", bAICanSeePlayer);
}



