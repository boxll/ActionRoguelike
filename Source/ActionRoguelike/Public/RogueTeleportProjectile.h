// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueProjectile.h"
#include "RogueTeleportProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARogueTeleportProjectile : public ARogueProjectile
{
	GENERATED_BODY()

public:
	ARogueTeleportProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* TeleportEffectComp;

	UFUNCTION()
	void Denotation();

	UFUNCTION()
	void Teleport();
};
