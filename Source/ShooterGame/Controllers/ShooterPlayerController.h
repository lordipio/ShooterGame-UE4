// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, Category = "Player Win Condition Widgets")
	TSubclassOf<class UUserWidget> PlayerWonWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Player Win Condition Widgets")
	TSubclassOf<class UUserWidget> PlayerLoseWidget;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> HealthBarWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	TSubclassOf<class UUserWidget> StartGameWidget;

	UPROPERTY(EditDefaultsOnly, Category = "HUD")
	TSubclassOf<class UUserWidget> CrossAimWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	TSubclassOf<class UUserWidget> MenuWidget;

	UPROPERTY(EditDefaultsOnly, Category = "Menu")
	TSubclassOf<class UUserWidget> EndGameWidget;

	class UUserWidget* CrossAim;

	virtual void BeginPlay() override;
	
	virtual void RestartLevel() override;
	
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UFUNCTION(BlueprintCallable)
	void RestartLevelFromBlueprint();

	void ShowEndGameWidget();

	void CreateStartGameWidget();

	void Menu();

	UPROPERTY(EditAnywhere)
	float ShowEndGameWidgetTime = 4.f;

	UPROPERTY(EditDefaultsOnly)
	float StartGameWidgetDelay = 2.5f;

};
