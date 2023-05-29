// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RogueHUD.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ARogueHUD : public AHUD
{
public:
	ARogueHUD();

private:
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateAndShowUserWidget(TSubclassOf<UUserWidget> UserWidgetClass);
	UFUNCTION(BlueprintCallable)
	void HideUserWidget(UUserWidget* UserWidget);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> CrossHairClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* CrossHair;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UUserWidget> HealthBarClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UUserWidget* HealthBar;
};
