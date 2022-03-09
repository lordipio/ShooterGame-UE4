// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGame/Controllers/ShooterPlayerController.h"
#include "ShooterGame/Characters/BaseCharacter.h"
#include "EngineUtils.h"



void AKillEmAllGameMode::PawnKilled(APawn* KilledPawn)
{
	AShooterPlayerController* PlayerController = Cast<AShooterPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (!PlayerController)
		return;

	float bIsEnemyAlive = false;

	if (KilledPawn == UGameplayStatics::GetPlayerPawn(GetWorld(), 0))
	{
		PlayerController->GameHasEnded(KilledPawn, false);
		KilledPawn->DetachFromControllerPendingDestroy();
		return;
	}

	else
	{
		for (ABaseCharacter* BaseCharacter : TActorRange<ABaseCharacter>(GetWorld()))
		{
			if (BaseCharacter->IsPlayerControlled())
			{
				continue;
			}
			if (!BaseCharacter->bIsDead)
			{
				bIsEnemyAlive = true;
				break;
			}
		}
	}
	if (!bIsEnemyAlive)
		PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
}
