// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RogueUserWidget.h"
#include "Components/Image.h"
#include "RogueUWCrosshair.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API URogueUWCrosshair : public URogueUserWidget
{
	GENERATED_BODY()

public:

protected:
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	UImage* TopImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	UImage* BottomImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	UImage* LeftImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidgetOptional))
	UImage* RightImage;
	UPROPERTY(BlueprintReadWrite, meta=(BindWidget))
	UImage* CenterImage;
};
