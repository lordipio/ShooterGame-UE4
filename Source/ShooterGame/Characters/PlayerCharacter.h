// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "PlayerCharacter.generated.h"

class AGun;
UCLASS()
class SHOOTERGAME_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Called every frame

	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Fire();

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float MaxWalkSpeedForPatrolling = 250.f;

	UPROPERTY(EditDefaultsOnly, Category = "Speed")
	float MaxWalkSpeedForFollowingPlayer = 500.f;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void MoveForward(float Value);

	virtual void MoveRight(float Value);

private:

	class AController* PlayerController;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComp;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CharacterForwardMovementSpeed = 0.01f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float CharacterRightMovementSpeed = 0.01f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	float MouseSpeed = 10.f;

	void ChangeCameraProccess();

	void ChangeCameraKeyPressed();

	void KillCharacter();

	void AimX(float Value);

	void AimY(float Value);

	void SprintKey(float Value);
	
	void CameraAiming(float Value);

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmPosition", meta = (AllowPrivateAccess = "true"))
	FVector SpringArmSecondLocation;

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmPosition", meta = (AllowPrivateAccess = "true"))
	FVector SpringArmFirstLocation;

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmPosition", meta = (AllowPrivateAccess = "true"))
	FVector CameraAimLocation;

	UPROPERTY(EditDefaultsOnly, Category = "SpringArmPosition", meta = (AllowPrivateAccess = "true"))
	float SpringArmAimTargetArmLength = 108.907402;

	float DefaultSpringArmTargetArmLength;

	float Sprint = 0.f;

	float DefaultMaxAcceleration;

	float DefaultBrakingDecceleration;

	bool SpringArmFirstToSecondPending = false;

	bool SpringArmSecondToFirstPending = false;

	bool LoopPermision = true;

	bool bChangeCameraKeyPressed = false;

};
