// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SHOOTERGAME_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SpawnShootEmitter();

	void SpawnImpactEmitter(FVector ParticleLocation, FRotator ParticleRotation);

	void SpawnShootSound();

	void SpawnImpactSound(FVector);

	void TakeDamage(FHitResult& Hit, FVector& ShotDirection);

	UPROPERTY(EditDefaultsOnly, Category = "Shooting Range")
	float ShootingRange = 1000.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ShootParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Particles", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* ImpactParticle;

	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* GunSpawnPoint;

	UPROPERTY(EditDefaultsOnly, Category = "ImpactSound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* ImpactSound;

	UPROPERTY(EditDefaultsOnly, Category = "ShootSound", meta = (AllowPrivateAccess = "true"))
	class USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly, Category = "Damage", meta = (AllowPrivateAccess = "true"))
	float DamageAmount = 10.f;

};
