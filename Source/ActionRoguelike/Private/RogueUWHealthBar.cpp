// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUWHealthBar.h"

#include "RogueHealthComponent.h"
#include "Components/CanvasPanelSlot.h"

void URogueUWHealthBar::NativeConstruct()
{
	Super::NativeConstruct();

	if(APawn* Owner = GetOwningPlayerPawn())
	{
		if(URogueHealthComponent* HealthComp = Cast<URogueHealthComponent>(Owner->GetComponentByClass(URogueHealthComponent::StaticClass())))
		{
			HealthComp->OnHealthChangedDelegate.AddDynamic(this, &URogueUWHealthBar::UpdateHealthBar);
		}
	}
}

void URogueUWHealthBar::UpdateHealthBar(URogueHealthComponent* HealthComp, float OldValue, float NewValue,
	AActor* Instigator)
{
	FNumberFormattingOptions Opts;
	Opts.SetMaximumFractionalDigits(0);
	HealthNumberLabel->SetText(FText::AsNumber(NewValue, &Opts));

	float NewPercent = NewValue / HealthComp->GetMaxHealth();
	float OldPercent = OldValue / HealthComp->GetMaxHealth();

	UCanvasPanelSlot* DeltaHealthImageSlot = Cast<UCanvasPanelSlot>(DeltaHealthImage->Slot);
	DeltaHealthImageSlot->SetAnchors(FAnchors(NewPercent, 0.0f, OldPercent, 1.0f));
	
	HealthBar->SetPercent(NewPercent);
	if(OldValue>NewValue)
	{
		PlayAnimation(HealthDecreaseAnim);
	}
}
