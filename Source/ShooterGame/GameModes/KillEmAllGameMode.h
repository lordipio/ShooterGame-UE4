// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ShooterGameGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AKillEmAllGameMode : public AShooterGameGameModeBase
{
	GENERATED_BODY()
public:
	virtual void PawnKilled(APawn* KilledPawn) override;
};
