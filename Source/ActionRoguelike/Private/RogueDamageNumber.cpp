// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueDamageNumber.h"

#include "Components/OverlaySlot.h"

void URogueDamageNumber::Initialize(float _duration)
{
	Duration = _duration;

	BeginPadding = Cast<UOverlaySlot>(this->Slot)->Padding;
	TargetPadding = BeginPadding * 2;
}

void URogueDamageNumber::Update(float InDeltaTime)
{
	if(IsComplete())
	{
		return;
	}

	LifeTime+=InDeltaTime;

	UOverlaySlot* OverlaySlot = Cast<UOverlaySlot>(this->Slot);
	OverlaySlot->SetPadding(FMath::Lerp<FVector4>(FVector4(BeginPadding.Left, BeginPadding.Top, BeginPadding.Right, BeginPadding.Bottom)
		, FVector4(TargetPadding.Left, TargetPadding.Top, TargetPadding.Right, TargetPadding.Bottom)
		, LifeTime/Duration));
}