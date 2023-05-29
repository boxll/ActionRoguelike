// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueHUD.h"

#include "Blueprint/UserWidget.h"

ARogueHUD::ARogueHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> CrossHairClassFinder (TEXT("/Game/ActionRoguelike/UI/WBP_Crosshair"));
	CrossHairClass = CrossHairClassFinder.Class;
}

void ARogueHUD::BeginPlay()
{
	Super::BeginPlay();

	CrossHair = CreateAndShowUserWidget(CrossHairClass);
	HealthBar = CreateAndShowUserWidget(HealthBarClass);
}

UUserWidget* ARogueHUD::CreateAndShowUserWidget(TSubclassOf<UUserWidget> UserWidgetClass)
{
	if(!UserWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Parameter of ARogueHUD::CreateAndShowUserWidget is missing! Nothing was created."));
		return nullptr;
	}

	APlayerController* PC = Cast<APlayerController>(GetOwner());
	UUserWidget* NewUserWidget = CreateWidget(PC, UserWidgetClass);

	NewUserWidget->AddToViewport();

	return NewUserWidget;

}

void ARogueHUD::HideUserWidget(UUserWidget* UserWidget)
{
	if ( UserWidget )
	{
		UserWidget->RemoveFromViewport();
	}
}
