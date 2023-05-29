// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUWHealthBar.h"

#include "RogueHealthComponent.h"

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

	HealthBar->SetPercent(NewValue / HealthComp->GetMaxHealth());
}
