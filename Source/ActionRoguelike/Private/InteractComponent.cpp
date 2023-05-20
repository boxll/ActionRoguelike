// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractComponent.h"

#include "EngineUtils.h"
#include "InteractInterface.h"
#include "Util/ColorConstants.h"

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
	FVector ViewBeginLocation;
	FVector ViewEndLocation;
	if(ARogueCharacter* OwnerRogueCharacter = Cast<ARogueCharacter>(GetOwner()))
	{
		OwnerRogueCharacter->GetCameraViewVector(ViewBeginLocation, ViewEndLocation, 120.0f);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s owned by wrong character class"), *this->GetClass()->GetName());
		check(false);
		return;
	}
	
	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->SweepMultiByObjectType( OutHits, ViewBeginLocation
		, ViewEndLocation
		, FQuat::Identity
		, FCollisionObjectQueryParams( ECollisionChannel::ECC_WorldDynamic )
		, FCollisionShape::MakeSphere(50.0f) );

	// DrawDebugLine(GetWorld(), EyeLocation, EyeLocation + (EyeRotation.Vector() * 100), FColor::Red, false, 5.0f, 0.0f, 2.0f);

	for (FHitResult Hit : OutHits)
	{
		if (AActor* HitActor = Hit.GetActor())
		{
			if (IInteractInterface* Interface = Cast<IInteractInterface>(HitActor)) // if(HitActor->Implements<UInteractInterface>())
			{
				Interface->Execute_Interact(HitActor, Cast<ARogueCharacter>(GetOwner()));  // IInteractInterface::Execute_Interact(HitActor, Cast<ARogueCharacter>(GetOwner()));
				break;
			}
		}
	}
}