// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueHealthComponent.h"
#include "RogueUserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "RogueUWHealthBar.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueUWHealthBar : public URogueUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UFUNCTION()
	void UpdateHealthBar(URogueHealthComponent* HealthComp, float OldValue, float NewValue, AActor* Instigator);
	
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UTextBlock* HealthNumberLabel;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UProgressBar* HealthBar;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* DeltaHealthImage;
	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* HealthDecreaseAnim;
};
