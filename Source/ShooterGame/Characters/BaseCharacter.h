// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class AGun;
UCLASS()
class SHOOTERGAME_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Fire();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	float GetHealthPercentage();

	UPROPERTY(BlueprintReadOnly)
	bool bIsFire = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsDead = false;

protected:
	// Called when the game starts or when spawned
	class AGun* Gun;

	virtual void BeginPlay() override;
	
	void GetPlayerStartAndEndShootLocation(FVector& StartShootLoc, FVector& EndShootLoc, FRotator& PlayerStartLookingRot);

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	float Health = 100.f;

	float DefaultHealth;

private:

	class AController* PlayerController;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AGun> GunSubClass;

	void SetupGun();

	void SetIsFireFalse();
	

};
