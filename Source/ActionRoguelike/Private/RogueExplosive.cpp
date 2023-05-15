// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueExplosive.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ARogueExplosive::ARogueExplosive()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialForce");
	RadialForce->SetupAttachment(RootComponent);
	RadialForce->Radius = 500;
	RadialForce->ImpulseStrength = 200;
	RadialForce->bImpulseVelChange = 1;
	RadialForce->bIgnoreOwningActor = 1;

	Exploded = false;
}

// Called when the game starts or when spawned
void ARogueExplosive::BeginPlay()
{
	Super::BeginPlay();
	Mesh->OnComponentHit.AddDynamic(this, &ARogueExplosive::TryExplode);
}

void ARogueExplosive::TryExplode(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(!Exploded)
	{
		RadialForce->FireImpulse();
		Exploded = true;
	}
	
}

// Called every frame
void ARogueExplosive::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

