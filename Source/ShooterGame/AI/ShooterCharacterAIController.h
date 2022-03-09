// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterCharacterAIController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AShooterCharacterAIController : public AAIController
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "BehaviorTree")
	class UBehaviorTree* BehaviorTree;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class APlayerCharacter> PlayerCharacterSubclass;
	
	AActor* PlayerActor;
	
	class APlayerCharacter* PlayerCharacter;

	bool bAICanSeePlayer = false;

	float EnemyDepthOfField = 600.f;
};
