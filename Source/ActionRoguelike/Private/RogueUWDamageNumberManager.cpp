// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueUWDamageNumberManager.h"

#include "Blueprint/WidgetTree.h"
#include "Components/OverlaySlot.h"

void URogueUWDamageNumberManager::NativeConstruct()
{
	Super::NativeConstruct();

	DamageNumberCanvas->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void URogueUWDamageNumberManager::AddDamageNumber(float Damage)
{
	UOverlay* RootWidget = Cast<UOverlay>(GetRootWidget());
	ensure(RootWidget);

	URogueDamageNumber* DamageNumberText = this->WidgetTree->ConstructWidget<URogueDamageNumber>(URogueDamageNumber::StaticClass());
	DamageNumberText->SetText(FText::FromString(FString::FromInt(FMath::FloorToInt(Damage))));

	UOverlaySlot* DmgTxtSlot = RootWidget->AddChildToOverlay(DamageNumberText);
	DmgTxtSlot->SetHorizontalAlignment(HAlign_Center);
	DmgTxtSlot->SetVerticalAlignment(VAlign_Center);
	DmgTxtSlot->SetPadding(RandPtOnRectEdge(120.0f, 200.0f));

	DamageNumberText->Initialize(1.5f);

	NumbersToAdd.Add(DamageNumberText);
}

void URogueUWDamageNumberManager::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	for(int32 i = ActiveNumbers.Num()-1; i >= 0; --i)
	{
		URogueDamageNumber* DmgNumb = ActiveNumbers[i];
		DmgNumb->Update(InDeltaTime);
		if(DmgNumb->IsComplete())
		{
			ActiveNumbers.RemoveAt(i);
			DmgNumb->RemoveFromParent();
		}
	}

	for ( int32 i = 0; i < NumbersToAdd.Num(); ++i )
	{
		ActiveNumbers.Add( NumbersToAdd[ i ] );
	}
	NumbersToAdd.Empty();
}

FMargin URogueUWDamageNumberManager::RandPtOnRectEdge(float HalfRectWidth, float HalfRectHeight)
{
	float RandLength = FMath::FRandRange(0, HalfRectWidth*4 + HalfRectHeight*4);

	//going from top left clockwise
	if (RandLength<HalfRectWidth*2)
	{
		//top edge
		return FMargin(RandLength - HalfRectWidth, 0, 0, HalfRectHeight);
	}
	if (RandLength < HalfRectWidth*2+HalfRectHeight*2)
	{
	 	//right edge
	 	return FMargin(HalfRectWidth, 0, 0, HalfRectHeight - (RandLength - HalfRectWidth*2) );
	 }
	if (RandLength < HalfRectWidth*4+HalfRectHeight*2)
	{
		//bottem edge
		return FMargin(HalfRectWidth - (RandLength - (HalfRectWidth*2+HalfRectHeight*2)), 0, 0, -HalfRectHeight );
	}

	//left edge
	return FMargin(-HalfRectWidth, 0, 0, RandLength - (HalfRectWidth*4+HalfRectHeight*2) - HalfRectHeight );

}
