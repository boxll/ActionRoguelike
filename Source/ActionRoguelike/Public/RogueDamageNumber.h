// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextBlock.h"
#include "RogueDamageNumber.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueDamageNumber : public UTextBlock
{
	GENERATED_BODY()

public:
	
	void Initialize(float _duration);
	void Update(float InDeltaTime);
	bool IsComplete() const {return LifeTime>Duration;};

protected:

	float Duration;
	float LifeTime = 0.0f;
	FMargin BeginPadding;
	FMargin TargetPadding;
	
};
