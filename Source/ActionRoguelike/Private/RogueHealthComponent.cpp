// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHealthComponent.h"

#include <algorithm>

// Sets default values for this component's properties
URogueHealthComponent::URogueHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

bool URogueHealthComponent::ApplyHealthChange(float Delta)
{
	if(isnan(Delta)){return false;}

	Health= std::clamp(Health + Delta, 0.0f, MaxHealth);

	return true;
}


// Called when the game starts
void URogueHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;
	// ...
	
}


// Called every frame
void URogueHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

