// Fill out your copyright notice in the Description page of Project Settings.


#include "RogueCharacter.h"
#include "RogueProjectile.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ARogueCharacter::ARogueCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractComp = CreateDefaultSubobject<UInteractComponent>("InteractComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ARogueCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARogueCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARogueCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ARogueCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ARogueCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ARogueCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ARogueCharacter::Jump);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ARogueCharacter::Interact);
}

void ARogueCharacter::MoveForward(float Input)
{
	const FRotator ControlRot = GetControlRotation();
	const FRotator ForwardRot = FRotator(0, ControlRot.Yaw, 0);

	AddMovementInput(ForwardRot.Vector(), Input);
}

void ARogueCharacter::MoveRight(float Input)
{
	const FRotator ControlRot = GetControlRotation();
	// Rotate forward to right, borrow from UKismetMathLibrary::GetRightVector
	const FVector RightVec = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);
	
	AddMovementInput(RightVec, Input);
}

void ARogueCharacter::PrimaryAttack()
{
	PlayAnimMontage(PrimaryAttackAnim);

	FTimerHandle TempHandle;
	GetWorldTimerManager().SetTimer(TempHandle, this, &ARogueCharacter::SpawnPrimaryBullet, 0.28f, false);
}

void ARogueCharacter::Interact()
{
	InteractComp->Interact();
}

void ARogueCharacter::SpawnPrimaryBullet()
{
	const FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

	FVector ViewBeginLocation;
	FVector ViewEndLocation;
	GetCameraViewVector(ViewBeginLocation, ViewEndLocation, 10000.0f);
	
	const FTransform SpawnTM = FTransform((ViewEndLocation - HandLocation).ToOrientationRotator(), HandLocation);

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	GetWorld()->SpawnActor<AActor>(PrimaryProjectileClass, SpawnTM, SpawnParams);	
}

void ARogueCharacter::GetCameraViewVector(FVector& BeginLocation, FVector& EndLocation, float VectorLength = 100.0f)
{
	FRotator ViewRotation = GetControlRotation();
	BeginLocation = this->CameraComp->GetComponentLocation() + ViewRotation.Vector() * SpringArmComp->TargetArmLength;
	
	EndLocation = BeginLocation + (ViewRotation.Vector() * VectorLength);

	TArray<FHitResult> OutHits;
	bool bHit = GetWorld()->LineTraceMultiByChannel(OutHits, BeginLocation,
		EndLocation, ECC_Visibility );

	if(bHit)
	{
		EndLocation = OutHits[0].Location;
	}

}
