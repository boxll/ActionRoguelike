// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueBlackholeProjectile.h"

ARogueBlackholeProjectile::ARogueBlackholeProjectile()
{
	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->bAutoActivate = false;
	RadialForce->Radius = 500.0f;
	RadialForce->ForceStrength = -10000.0f; // Negative number to suck in stuffs
	RadialForce->RemoveObjectTypeToAffect(UEngineTypes::ConvertToObjectType(ECC_Pawn));
}

void ARogueBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARogueBlackholeProjectile::DestroyTouchedActors);
}

void ARogueBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle SelfDestoryHandle;
	FTimerDelegate SelfDestoryDelegate = FTimerDelegate::CreateUObject(this, &AActor::K2_DestroyActor);
	GetWorldTimerManager().SetTimer(SelfDestoryHandle, SelfDestoryDelegate, 5.0f, false);

	FTimerHandle ActivateRadialForceHandle;
	FTimerDelegate ActivateRadialForceDelegate = FTimerDelegate::CreateUObject(RadialForce, &UActorComponent::Activate, false);
	GetWorldTimerManager().SetTimer(ActivateRadialForceHandle, ActivateRadialForceDelegate, 0.6f, false);
}

void ARogueBlackholeProjectile::DestroyTouchedActors(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(OtherComp->GetCollisionObjectType() == ECC_PhysicsBody)
	{
		OtherActor->Destroy();
	}
}
