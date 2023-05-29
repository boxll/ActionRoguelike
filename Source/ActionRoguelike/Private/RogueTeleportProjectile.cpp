// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueTeleportProjectile.h"

ARogueTeleportProjectile::ARogueTeleportProjectile()
{
	MovementComp->InitialSpeed = 4000.0f;

	TeleportEffectComp = CreateDefaultSubobject<UParticleSystemComponent>("TeleportEffectComp");
	TeleportEffectComp->SetupAttachment(RootComponent);
	TeleportEffectComp->bAutoActivate = false;

	Damage = 0;
}

void ARogueTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DenotationHandle;
	GetWorldTimerManager().SetTimer(DenotationHandle, this, &ARogueTeleportProjectile::Denotation, 0.2f, false);
}

void ARogueTeleportProjectile::Denotation()
{
	//Play Denotation Effect
	TeleportEffectComp->Activate();
	MovementComp->StopMovementImmediately();

	FTimerHandle TeleportHandle;
	GetWorldTimerManager().SetTimer(TeleportHandle, this, &ARogueTeleportProjectile::Teleport, 0.2f, false);
}

void ARogueTeleportProjectile::Teleport()
{
	Owner->TeleportTo(GetActorLocation(), Owner->GetActorRotation());
	Destroy();
}
