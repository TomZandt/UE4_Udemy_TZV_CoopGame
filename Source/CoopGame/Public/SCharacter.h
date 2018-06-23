// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Sets default values for this character's properties
	ASCharacter();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Call to move the player in the forward axis by the incoming value
	void MoveForward(float Value);

	// Call to move the player in the right axis by the incoming value
	void MoveRight(float Value);

	// Call to begin crouch
	void BeginCrouch();

	// Call to end crouch
	void EndCrouch();

	// Create a pointer for the characters camera component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* pCameraComponent;

	// Create a pointer for the characters spring arm component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* pSpringArmComponent;

	// Create a variable to offset the "SpringArmComponent"
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FVector SpringArmComponentOffset;

public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Override "GetPawnViewLocation" to return the position of the camera
	virtual FVector GetPawnViewLocation() const override;
};
