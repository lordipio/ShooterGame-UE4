// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("GunSpawnPoint"));

	RootComponent = GunSpawnPoint;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));

	SkeletalMesh->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AGun::SpawnShootEmitter()
{

	if (ShootParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(ShootParticle, SkeletalMesh, TEXT("MuzzleFlashSocket"), ((FVector)(ForceInit)), FRotator::ZeroRotator, ((FVector)((0.45F))), EAttachLocation::SnapToTarget);
	}

}


void AGun::SpawnImpactEmitter(FVector ParticleLocation, FRotator ParticleRotation)
{
	if (ImpactParticle)
	{
		FTransform Transform;
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticle, ParticleLocation, ParticleRotation, ((FVector)((1.5f))));
	}
}


void AGun::SpawnShootSound()
{
	UGameplayStatics::SpawnSoundAttached(ShootSound, SkeletalMesh, TEXT("MuzzleFlashSocket"));
}


void AGun::SpawnImpactSound(FVector ImpactLocation)
{
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, ImpactLocation);
}


void AGun::TakeDamage(FHitResult& Hit, FVector& ShotDirection)
{
	FPointDamageEvent PointDamage;
	PointDamage.Damage = DamageAmount;
	PointDamage.HitInfo = Hit;
	PointDamage.ShotDirection = ShotDirection;

	if (UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		Hit.GetActor()->TakeDamage(DamageAmount, PointDamage, UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)->GetInstigatorController(), this);
	}
}
