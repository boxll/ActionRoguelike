// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosive.h"

// Sets default values
ARogueExplosive::ARogueExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

}

// Called when the game starts or when spawned
void ARogueExplosive::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

