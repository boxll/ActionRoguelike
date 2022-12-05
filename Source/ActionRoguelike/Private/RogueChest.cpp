// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueChest.h"


// Sets default values
ARogueChest::ARogueChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
}

// Called when the game starts or when spawned
void ARogueChest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARogueChest::Interact_Implementation(ARogueCharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("HelloWorld"));
}

