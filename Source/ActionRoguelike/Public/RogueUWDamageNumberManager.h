// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueDamageNumber.h"
#include "RogueUserWidget.h"
#include "Components/Overlay.h"
#include "RogueUWDamageNumberManager.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueUWDamageNumberManager : public URogueUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void AddDamageNumber(float Damage);
	
protected:

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY()
	TArray<URogueDamageNumber*> NumbersToAdd;

	UPROPERTY()
	TArray<URogueDamageNumber*> ActiveNumbers;

	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UOverlay* DamageNumberCanvas;

	FMargin RandPtOnRectEdge(float RectWidth, float RectHeight);

};