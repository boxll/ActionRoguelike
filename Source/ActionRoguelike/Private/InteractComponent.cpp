// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "EngineUtils.h"
#include "InteractInterface.h"

// Sets default values for this component's properties
UInteractComponent::UInteractComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UInteractComponent::Interact()
{
	FVector EyeLocation;
	FRotator EyeRotation;
	GetOwner() -> GetActorEyesViewPoint(EyeLocation, EyeRotation);
	
	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByObjectType( OutHits, EyeLocation
		, EyeLocation + (EyeRotation.Vector() * 1000)
		, FQuat::Identity
		, FCollisionObjectQueryParams( ECollisionChannel::ECC_WorldDynamic )
		, FCollisionShape::MakeSphere(30.0f) );

	for (FHitResult Hit : OutHits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (IInteractInterface* Interface = Cast<IInteractInterface>(HitActor))
			{
				Interface->Execute_Interact(HitActor, Cast<ARogueCharacter>(GetOwner()));
				break;
			}
		}
	}
}