// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractComponent.h"
#include "RogueProjectile.h"
#include "GameFramework/Character.h"
#include "RogueCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UAnimMontage;

UCLASS()
class ACTIONROGUELIKE_API ARogueCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARogueCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetCameraViewVector(FVector& BeginLocation, FVector& EndLocation, float VectorLength);

protected:
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere)
	UInteractComponent* InteractComp;

	UPROPERTY(EditAnywhere, Category="PrimaryAttack")
	TSubclassOf<ARogueProjectile> PrimaryProjectileClass;

	UPROPERTY(EditAnywhere, Category="PrimaryAttack")
	TSubclassOf<ARogueProjectile> Ability1ProjectileClass;
	UPROPERTY(EditAnywhere, Category="PrimaryAttack")

	TSubclassOf<ARogueProjectile> UltimateProjectileClass;

	UPROPERTY(EditAnywhere, Category="PrimaryAttack")
	UAnimMontage* PrimaryAttackAnim;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Input);
	void MoveRight(float Input);

	UFUNCTION()
	void ProjectileAbility(TSubclassOf<ARogueProjectile> ProjectileClass);
	DECLARE_DELEGATE_OneParam(FProjectileAbilityDelegate, TSubclassOf<ARogueProjectile>);

	void Interact();
	void SpawnProjectile(TSubclassOf<ARogueProjectile> ProjectileClass);

};
