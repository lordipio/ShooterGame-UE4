// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
	UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->DisableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));

	if (GetWorld()->GetMapName() == "UEDPIE_0_Map1")
	{
		CrossAim = CreateWidget(this, CrossAimWidget);
		CrossAim->AddToViewport();

		FTimerHandle TimerHandler;
		GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &AShooterPlayerController::CreateStartGameWidget, StartGameWidgetDelay, false);

		UUserWidget* HealthBar = CreateWidget(this, HealthBarWidget);
		HealthBar->AddToViewport();

		UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = false;
		UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->EnableInput(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	}
}

void AShooterPlayerController::RestartLevel()
{
	Super::RestartLevel();
}



void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, false);

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AShooterPlayerController::ShowEndGameWidget, ShowEndGameWidgetTime);

	if (!bIsWinner)
	{
		UUserWidget* Lose = CreateWidget(this, PlayerLoseWidget);
		Lose->AddToViewport();
		CrossAim->RemoveFromParent();
	}

	if (bIsWinner)
	{
		UUserWidget* Win = CreateWidget<UUserWidget, AShooterPlayerController>(this, PlayerWonWidget);
		Win->AddToViewport();
		CreateWidget(this, CrossAimWidget)->RemoveFromParent();
	}
}



void AShooterPlayerController::CreateStartGameWidget()
{
	UUserWidget* StartGame = CreateWidget(this, StartGameWidget);
	StartGame->AddToViewport();
}



void AShooterPlayerController::Menu()
{
	UUserWidget* Menu = CreateWidget<UUserWidget, AShooterPlayerController>(this, MenuWidget);
	Menu->AddToViewport();
	SetPause(true);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}



void AShooterPlayerController::RestartLevelFromBlueprint()
{
	RestartLevel();
}



void AShooterPlayerController::ShowEndGameWidget()
{
	SetPause(true);
	UUserWidget* EndGame = CreateWidget<UUserWidget, AShooterPlayerController>(this, EndGameWidget);
	EndGame->AddToViewport();
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->bShowMouseCursor = true;
}