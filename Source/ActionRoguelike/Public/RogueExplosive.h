// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "RogueExplosive.generated.h"

UCLASS()
class ACTIONROGUELIKE_API ARogueExplosive : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ARogueExplosive();

protected:
	virtual void PostInitializeComponents() override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* RadialForce;

	UFUNCTION()
	void TryExplode( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	bool Exploded;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
