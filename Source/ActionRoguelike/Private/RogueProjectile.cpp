// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueProjectile.h"

#include "RogueHealthComponent.h"

// Sets default values
ARogueProjectile::ARogueProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	// SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(RootComponent);
	
	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->ProjectileGravityScale = 0.0f;
	
}

void ARogueProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ARogueProjectile::OnSphereCompHit);
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ARogueProjectile::OnSphereCompBeginOverlap);
}

// Called when the game starts or when spawned
void ARogueProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARogueProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARogueProjectile::OnSphereCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DoProjectileDamageToActor(OtherActor);
}

void ARogueProjectile::OnSphereCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	DoProjectileDamageToActor(OtherActor);
}

void ARogueProjectile::DoProjectileDamageToActor(AActor* Actor)
{
	if(Actor)
	{
		URogueHealthComponent* HealthComp = Cast<URogueHealthComponent>(Actor->GetComponentByClass(URogueHealthComponent::StaticClass()));
		if(HealthComp)
		{
			HealthComp->ApplyHealthChange(-Damage);
			Destroy();
		}
	}
}
