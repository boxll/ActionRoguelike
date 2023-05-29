// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RogueHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChangedSignature, URogueHealthComponent*, HealthComp, float, OldValue, float, NewValue, AActor*, Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API URogueHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URogueHealthComponent();

	UFUNCTION(BlueprintCallable)
	bool ApplyHealthChange(float Delta);

	UPROPERTY(BlueprintAssignable)
	FOnHealthChangedSignature OnHealthChangedDelegate;

	float GetHealth();
	float GetMaxHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float MaxHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
