// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ShooterGame/Controllers/ShooterPlayerController.h"



// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	DefaultMaxAcceleration = GetCharacterMovement()->GetMaxAcceleration();

	GetCharacterMovement()->MaxWalkSpeed = 600.f;

	DefaultBrakingDecceleration = GetCharacterMovement()->BrakingDecelerationWalking;

	DefaultSpringArmTargetArmLength = SpringArmComp->TargetArmLength;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bChangeCameraKeyPressed)
	{
		ChangeCameraProccess();
	}

	if (bIsDead && LoopPermision)
	{
		KillCharacter();
		LoopPermision = false;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Aim", this, &APlayerCharacter::CameraAiming);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerCharacter::Fire);

	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &ACharacter::Jump);

	PlayerInputComponent->BindAction("ChangeCamera", EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeCameraKeyPressed);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);

	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Sprint", this, &APlayerCharacter::SprintKey);

	PlayerInputComponent->BindAxis("MouseX", this, &APlayerCharacter::AimX);

	PlayerInputComponent->BindAxis("MouseY", this, &APlayerCharacter::AimY);

	AShooterPlayerController* ShooterPlayerController = Cast<AShooterPlayerController>(GetController());

	if (ShooterPlayerController)
	{
		PlayerInputComponent->BindAction("Menu", EInputEvent::IE_Pressed, ShooterPlayerController, &AShooterPlayerController::Menu);
	}
}

void APlayerCharacter::Fire()
{
	Super::Fire();
}


void APlayerCharacter::MoveForward(float Value)
{
	CharacterForwardMovementSpeed += Sprint;

	AddMovementInput(GetActorForwardVector() * CharacterForwardMovementSpeed * Value, true);
}


void APlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector() * CharacterRightMovementSpeed * Value, true);
}


void APlayerCharacter::AimX(float Value)
{
	AddControllerYawInput(Value * MouseSpeed * GetWorld()->GetDeltaSeconds());
}


void APlayerCharacter::AimY(float Value)
{
	AddControllerPitchInput((-Value) * MouseSpeed * GetWorld()->GetDeltaSeconds());
}


void APlayerCharacter::SprintKey(float Value)
{

	if (Value && GetCharacterMovement()->MaxWalkSpeed == 600.f)
	{
		GetCharacterMovement()->MaxWalkSpeed = 800.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 400.f;
	}

	if (!Value && GetCharacterMovement()->MaxWalkSpeed == 800.f)
	{
		GetCharacterMovement()->MaxAcceleration = 0.f;
		GetCharacterMovement()->BrakingDecelerationWalking = 400.f;

		if (UGameplayStatics::GetPlayerPawn(this, 0)->GetVelocity().Size() < 620.f)
		{
			GetCharacterMovement()->MaxWalkSpeed = 600.f;
			GetCharacterMovement()->MaxAcceleration = DefaultMaxAcceleration;
			GetCharacterMovement()->BrakingDecelerationWalking = DefaultBrakingDecceleration;
		}
	}
}


void APlayerCharacter::KillCharacter()
{

	GetCapsuleComponent()->DestroyComponent();
}



void APlayerCharacter::ChangeCameraKeyPressed()
{
	bChangeCameraKeyPressed = true;
}



void APlayerCharacter::ChangeCameraProccess()
{
	FVector SpringArmCurrentLocation = SpringArmComp->GetRelativeLocation();
	if (SpringArmFirstToSecondPending)
	{
		SpringArmCurrentLocation = FMath::VInterpConstantTo(SpringArmCurrentLocation, SpringArmSecondLocation, GetWorld()->GetDeltaSeconds(), 300.f);


		SpringArmComp->SetRelativeLocation(SpringArmCurrentLocation);

		if (UKismetMathLibrary::InRange_FloatFloat(SpringArmCurrentLocation.Y, SpringArmSecondLocation.Y - 1, SpringArmSecondLocation.Y + 1))
		{
			UE_LOG(LogTemp, Error, TEXT("HELLO"));
			SpringArmFirstToSecondPending = false;
			bChangeCameraKeyPressed = false;
		}
	}

	if (SpringArmSecondToFirstPending)
	{
		SpringArmCurrentLocation.Y = FMath::FInterpConstantTo(SpringArmCurrentLocation.Y, SpringArmFirstLocation.Y, GetWorld()->GetDeltaSeconds(), 300.f);
		SpringArmComp->SetRelativeLocation(SpringArmCurrentLocation);
		if (UKismetMathLibrary::InRange_FloatFloat(SpringArmCurrentLocation.Y, SpringArmFirstLocation.Y - 1, SpringArmFirstLocation.Y + 1))
		{
			SpringArmSecondToFirstPending = false;
			bChangeCameraKeyPressed = false;
		}
	}


	if (!SpringArmFirstToSecondPending && !SpringArmSecondToFirstPending)
	{
		

		if (UKismetMathLibrary::InRange_FloatFloat(SpringArmCurrentLocation.Y, SpringArmFirstLocation.Y - 1, SpringArmFirstLocation.Y + 1))
		{
			SpringArmFirstToSecondPending = true;

		}

		if (UKismetMathLibrary::InRange_FloatFloat(SpringArmCurrentLocation.Y, SpringArmSecondLocation.Y - 1, SpringArmSecondLocation.Y + 1))
			SpringArmSecondToFirstPending = true;
	}


}


void APlayerCharacter::CameraAiming(float Value)
{
	
	FVector CameraCurrentLocation = SpringArmComp->GetRelativeLocation();

	if (Value)
	{
		SpringArmComp->SetRelativeLocation(CameraCurrentLocation);
		SpringArmComp->TargetArmLength = FMath::FInterpConstantTo(SpringArmComp->TargetArmLength, SpringArmAimTargetArmLength, GetWorld()->GetDeltaSeconds(), 300.f);
	}

	if (!Value)
	{
		SpringArmComp->SetRelativeLocation(CameraCurrentLocation);
		SpringArmComp->TargetArmLength = FMath::FInterpConstantTo(SpringArmComp->TargetArmLength, DefaultSpringArmTargetArmLength, GetWorld()->GetDeltaSeconds(), 300.f);
	}
}