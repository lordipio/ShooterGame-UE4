// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"
#include "ShooterGame/Actors/Gun.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterGame/GameModes/ShooterGameGameModeBase.h"
#include "Sound/SoundBase.h"



// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = GetController();
	DefaultHealth = Health;
	SetupGun();	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}



void ABaseCharacter::Fire()
{
	FTimerHandle TimerHandler;
	FHitResult Hit;
	FVector PlayerStartShootingLoc;
	FVector PlayerEndLook; 
	FRotator PlayerStartLookingRot;
	FCollisionQueryParams Param;
	
	// Is Firing
	bIsFire = true;
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, this, &ABaseCharacter::SetIsFireFalse, 0.01f); // this is for avoding crash
	GetPlayerStartAndEndShootLocation(PlayerStartShootingLoc, PlayerEndLook, PlayerStartLookingRot);

	// Hitting Actors
	Param.AddIgnoredActor(this);
	if (GetWorld()->LineTraceSingleByChannel(Hit, PlayerStartShootingLoc, PlayerEndLook, ECollisionChannel::ECC_GameTraceChannel1, Param))
	{
		if (Hit.GetActor())
		{
			FVector ShotDirection = -PlayerStartLookingRot.Vector();
			Gun->TakeDamage(Hit, ShotDirection);
		}
	}

	// Spawning Particles And Sounds
	Gun->SpawnShootEmitter();
	Gun->SpawnImpactEmitter(Hit.Location, (-PlayerStartLookingRot.Vector()).Rotation());
	Gun->SpawnShootSound();
	Gun->SpawnImpactSound(Hit.Location);
}



void ABaseCharacter::SetupGun()
{
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	if (GunSubClass)
	{
		Gun = GetWorld()->SpawnActor<AGun>(GunSubClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	}
}



void ABaseCharacter::SetIsFireFalse()
{
	bIsFire = false;
}




void ABaseCharacter::GetPlayerStartAndEndShootLocation(FVector& PlayerStartShootingLoc, FVector& PlayerEndLook, FRotator& PlayerStartLookingRot)
{
	FVector PlayerStartLookingLoc;

	if (UGameplayStatics::GetPlayerController(GetWorld(), 0) == GetController()) // if BaseCharacter was Player
	{
		PlayerController->GetPlayerViewPoint(PlayerStartLookingLoc, PlayerStartLookingRot);
	}

	else
	{
		PlayerStartLookingLoc = Gun->GetActorLocation();
		PlayerStartLookingRot = GetActorForwardVector().Rotation();
	}

	PlayerStartShootingLoc = PlayerStartLookingLoc;
	PlayerEndLook = PlayerStartLookingLoc + PlayerStartLookingRot.Vector() * Gun->ShootingRange;
}


float ABaseCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (DefaultHealth > 0)
	{
		DefaultHealth -= Damage;
	}

	if (DefaultHealth <= 0 && !bIsDead)
	{
		bIsDead = true;
		GetWorld()->GetAuthGameMode<AShooterGameGameModeBase>()->PawnKilled(this);
		DefaultHealth = 0;
	}

	return Damage;
}



float ABaseCharacter::GetHealthPercentage()
{
	return (DefaultHealth / Health);
}